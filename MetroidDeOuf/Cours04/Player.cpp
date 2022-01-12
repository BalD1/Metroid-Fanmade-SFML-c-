#include "stdafx.hpp"
#include "Player.hpp"
#include "Game.hpp"

Player::Player(std::string _name, int _cx, int _cy, int _stride) :
	Character(_name, _cx, _cy, _stride)
{
	this->initSprite();
	this->initWeapon();
	this->initSounds();
	this->initHPBar();
}

Player::Player( std::string _name, float _speed, float _invicibilityCD, float _maxHealth, int _cx, int _cy, int _stride) :
	Character(_name, _speed, _invicibilityCD, _maxHealth, _cx, _cy, _stride)
{
	this->initSprite();
	this->initWeapon();
	this->initSounds();
	this->initHPBar();
}

Player::~Player()
{
	delete(currentWeapon);
}

void Player::initSprite()
{
	this->texture = new sf::Texture();
	this->normalTexture = new sf::Texture();
	if (!normalTexture->loadFromFile(normalFormTexturePath))
		printf("Samus texture could not be loaded in %s", normalFormTexturePath);

	ballTexture = new sf::Texture();
	if (!ballTexture->loadFromFile(ballFormTexturePath))
		printf("Samus ball form texture could not be loaded in %s", ballFormTexturePath);

	this->texture = normalTexture;

	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);
	syncTransform();
}

void Player::initWeapon()
{
	this->currentWeapon = new Weapon();
	this->currentWeapon->worldRef = worldRef;
	this->currentWeapon->stride = stride;
}

void Player::initHPBar()
{
	barHolderTexture = new sf::Texture();
	if (!barHolderTexture->loadFromFile("Assets/Graphs/barholder.png"))
		printf("Bar holder texture could not be loaded in Assets/Graphs/barholder.png");

	this->barHolder = new sf::Sprite();
	this->barHolder->setTexture(*barHolderTexture);
	this->barHolder->move(barOffset);

	barTexture = new sf::Texture();
	if (!barTexture->loadFromFile("Assets/Graphs/bar.png"))
		printf("Bar texture could not be loaded in Assets/Graphs/bar.png");

	this->bar = new sf::Sprite();
	this->bar->setTexture(*barTexture);
	this->bar->move(barOffset);
}

void Player::initSounds()
{
	jumpSound = new sf::SoundBuffer();
	if (!jumpSound->loadFromFile("Assets/Sounds/jump.wav"))
		printf("Jump sound could not be loaded from Assets/Sounds/jump.wav");

	hurtSound = new sf::SoundBuffer();
	if (!hurtSound->loadFromFile("Assets/Sounds/playerhurt.wav"))
		printf("Hurt sound could not be loaded from Assets/Sounds/playerhurt.wav");

	deathSound = new sf::SoundBuffer();
	if (!deathSound->loadFromFile("Assets/Sounds/death.wav"))
		printf("Death sound could not be loaded from Assets/Sounds/death.wav");

	Character::initSounds();
}

void Player::setGame(Game* _gameRef)
{
	this->gameRef = _gameRef;
	gameRef->moveCamera(xx, yy);
	this->currentWeapon->gameRef = gameRef;
}

void Player::setWorld(World* _worldRef)
{
	this->worldRef = _worldRef;
	this->currentWeapon->worldRef = worldRef;
}

void Player::setAudioManager(AudioManager* _audiomanagerRef)
{
	this->audioManagerRef = _audiomanagerRef;
	this->currentWeapon->setAudiomanager(_audiomanagerRef);
}

void Player::im()
{
	ImGui::Text("Position and movements");
	moved |= (ImGui::DragInt("cx", &cx, 1));
	moved |= (ImGui::DragInt("cy", &cy, 1));
	moved |= (ImGui::DragFloat("rx", &rx, 0.05f));
	moved |= (ImGui::DragFloat("ry", &ry, 0.05f));
	ImGui::DragFloat("Speed", &speed, 1, 0, 100);
	ImGui::DragFloat("Jump Force", &jumpForce, 1, 1, 100);
	ImGui::DragFloat("Falling speed factor", &fallingSpeedFactor, 0.5f, 0);
	ImGui::DragFloat("Friction x", &frct_x, 0.05f, 0, 1);
	ImGui::DragFloat("Friction y", &frct_y, 0.05f, 0, 1);
	ImGui::Dummy(ImVec2(40, 0));
	ImGui::SameLine();
	if (ImGui::Button("Step up"))
	{
		moved = true;
		dy = -speed;
	}
	if (ImGui::Button("Step left"))
	{
		moved = true;
		dx = -speed;
	}
	ImGui::SameLine();
	if (ImGui::Button("Step right"))
	{
		moved = true;
		dx = speed;
	}
	ImGui::Dummy(ImVec2(35, 0));
	ImGui::SameLine();
	if (ImGui::Button("Step down"))
	{
		moved = true;
		dy = speed;
	}

	ImGui::Value("dx", (float)dx);
	ImGui::SameLine();
	ImGui::Value("dy", (float)dy);
	ImGui::SameLine();
	ImGui::Checkbox("Fly", &ignoreGravity);
	ImGui::Value("Jump Timer", (float)jumpTimer);
	ImGui::Value("Is Grounded", (bool)isGrounded);
	switch (characterState)
	{
		case Character::State::Idle:
			ImGui::Text("State : Idle");
			break;

		case Character::State::Walking:
			ImGui::Text("State : Walking");
			break;

		case Character::State::Jumping:
			ImGui::Text("State : Jumping");
			break;

		case Character::State::Falling:
			ImGui::Text("State : Falling");
			break;
	}

	ImGui::Separator();
	ImGui::Text("Health");
	ImGui::Text("HP : %f / %f", currentHealth, maxHealth);
	if (ImGui::Button("Revive"))
	{
		this->currentHealth = this->maxHealth;
		gameRef->setGameState(Game::GameState::InGame);
	}
	ImGui::Separator();
	ImGui::Text("Weapon");
	ImGui::DragFloat("Fire rate", &this->currentWeapon->fireCD, 0.5f, 0, 10);
	ImGui::DragInt("Knockback", &this->currentWeapon->knockbackForce, 1, 0, 20);
}

void Player::render(sf::RenderTarget& target)
{
	ImGui::Begin("Player tools");
	im();
	ImGui::End();
	ImGui::SFML::Render(target);

	states.transform = getTransform();
	target.draw(*this->spr, states);

	if (this->currentWeapon != nullptr)
		currentWeapon->render(target, states);

	target.draw(*this->barHolder, states);
	target.draw(*this->bar, states);
}

void Player::update(float dt)
{
	if (!alive())
		return;

	this->dt = dt;
	manageInputs();
	Character::update(dt);


	if (characterState == State::Jumping)
		jumpBehaviour();

	if (moved)
	{
		gameRef->moveCamera(this->xx, this->yy);
		gameRef->checkIfPlayerTouchCheckpoint();
		checkIfInDeathZone();
	}

	this->currentWeapon->update(dt);
	this->currentWeapon->mousePosition = gameRef->getMousePosition();
	this->currentWeapon->setPosition(cx, rx, cy, ry);
	this->currentWeapon->setOffset(sf::Vector2f(states.transform.getMatrix()[12] - gameRef->getMousePosition().x,
												states.transform.getMatrix()[13] - gameRef->getMousePosition().y));
}

void Player::manageInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		dx = -speed;
		//if (isFacingRight)
		//	flipSprite();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx = speed;
		//if (!isFacingRight)
		//	flipSprite();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		if (characterState != State::Falling)
			jump();
	if (sf::Joystick::isButtonPressed(1, Game::ControllerButtons::south))
		if (characterState != State::Falling)
			jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if (this->ignoreGravity)
			dy = speed;
	}

	float axisPosition = sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::X);
	if (axisPosition > joystickDeadZone || axisPosition < -joystickDeadZone)
		dx = axisPosition / 100 * speed;
}

void Player::manageEventInputs(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Down:
			if (isInNormalForm && inventory['ball'] >= 1)
				changeForm();
			break;

		case sf::Keyboard::Up:
			if (!isInNormalForm)
				changeForm();
			break;
	}
}

void Player::manageEventInputsRelease(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Space:
			characterState = State::Falling;
			jumpTimer = 0;
			break;
		default:
			break;
	}
}

void Player::manageEventAxis(sf::Joystick::Axis axis, float amount)
{
	switch (axis)
	{
	case sf::Joystick::PovY:
		if (amount > 50 || amount < -50)
			if (gameRef->GS == Game::GameState::InGame)
			{
				changeForm();
			}
		break;
	}
}

void Player::manageEventJoystickRelease(sf::Event::JoystickButtonEvent buttonEvent)
{
	switch (buttonEvent.button)
	{
		case Game::ControllerButtons::south:
			if (gameRef->GS == Game::GameState::InGame)
			{
				characterState = State::Falling;
				jumpTimer = 0;
			}
			break;
	}
}

void Player::fireWeapon()
{
	currentWeapon->fire();
}

void Player::jump()
{
	if (ignoreGravity)
	{
		dy = jumpForce * -1;
		return;
	}
	if (isGrounded && characterState != State::Jumping)
	{
		audioManagerRef->playSound(jumpSound, characterSoundPlayer);
		characterState = State::Jumping;
		jumpTimer = jumpLength;
		dy = jumpForce * -1;
	}
}

void Player::jumpBehaviour()
{
	if (jumpTimer > 0.01f)
	{
		dy = jumpForce * -1;
		jumpTimer -= dt;
	}
	else
	{
		characterState = State::Falling;
		jumpTimer = 0;
	}
}

void Player::checkIfInDeathZone()
{
	for (auto dz : worldRef->deathZones)
	{
		if (isCollidingSelf(dz->cx, dz->cy))
			this->kill();
	}
}

void Player::takeDamages(int rawDamages, int otherXX, int otherYY, int _knockbackForce)
{
	if (invincibility_Timer > 0)
		return;

	audioManagerRef->playSound(hurtSound, characterSoundPlayer);
	invincibility_Timer = invincibility_CD;
	this->currentHealth -= rawDamages;

	bar->setScale((this->currentHealth / this->maxHealth), 1);

	knockBack(otherXX, otherYY, _knockbackForce);

	if (currentHealth <= 0)
	{
		this->kill();
	}
}

void Player::heal(float rawHeal)
{
	this->currentHealth += rawHeal;
	if (this->currentHealth > maxHealth)
		this->currentHealth = maxHealth;

	bar->setScale((this->currentHealth / this->maxHealth), 1);
}

void Player::kill()
{
	audioManagerRef->stopMusic();
	characterSoundPlayer->setBuffer(*deathSound);
	characterSoundPlayer->play();
	this->currentHealth = 0;
	gameRef->setGameState(Game::GameState::GameOver);
}

void Player::flipSprite()
{
	if (isFacingRight)
	{
		this->spr->setTextureRect(sf::IntRect(this->spr->getTextureRect().width, 0, -this->spr->getTextureRect().width, this->spr->getTextureRect().height));
		isFacingRight = false;
	}
	else
	{
		this->spr->setTextureRect(sf::IntRect(this->spr->getTextureRect().width, 0, this->spr->getTextureRect().width, this->spr->getTextureRect().height));
		isFacingRight = true;
	}
}

void Player::changeForm()
{
	if (isInNormalForm)
	{
		this->texture = ballTexture;
		this->currentWeapon->canFire = false;
	}
	else
	{
		if (isCollidingWithWorld(cx, cy - 1))
			return;
		this->cy -= 1;
		this->texture = normalTexture;
		this->currentWeapon->canFire = true;
	}

	this->spr = new sf::Sprite();
	this->spr->setTexture(*texture);

	moved = true;
	isInNormalForm = !isInNormalForm;
}
