#include "stdafx.hpp"
#include "Game.hpp"

#pragma region Initiations

void Game::initWindow()
{
	mainView = new sf::View(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	this->window.create(sf::VideoMode(WIDTH, HEIGHT), "MetroidDeOuf", sf::Style::Close | sf::Style::Titlebar);
	this->window.setView(*mainView);
	window.setVerticalSyncEnabled(true);
	this->window.setFramerateLimit(60);

	ImGui::SFML::Init(this->window);

	windowSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	windowCenter = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);

	joystickMenuSelection_TIMER = joystickMenuSelection_CD;
}

void Game::closeWindow()
{
	this->window.close();
}

void Game::initMusic()
{
	audioManager.setMusic("Assets/Sounds/mainmenu.ogg");
}

void Game::initPlayer()
{
	this->player = new Player("Samus", 1,28, stride);
	this->player->setWorld(world);
	this->player->setGame(this);
	this->player->audioManagerRef = &this->audioManager;
	this->player->setGravity(gravity);
	this->player->joystickDeadZone = controllerDeadZone;
	charactersManager->playerRef = player;
}

void Game::initWorld()
{
	this->world = new World();
	world->gravity = this->gravity;
	this->charactersManager = new CharactersManager();
	charactersManager->worldRef = this->world;
	charactersManager->audioManager = &this->audioManager;
}

void Game::initFonts()
{
	titleFont = sf::Font();
	if (!titleFont.loadFromFile("Assets/Fonts/titlefont.ttf"))
		printf("Couldn't load Assets/Fonts/titlefont.ttf");
	baseFont = sf::Font();
	if (!baseFont.loadFromFile("Assets/Fonts/basefont.ttf"))
		printf("Couldn't load Assets/Fonts/basefont.ttf");


	stateText.setFont(baseFont);
	stateText.setCharacterSize(100);
	deactivateStateText();
}

void Game::initGrid()
{
	gridRct = sf::RectangleShape(sf::Vector2f(stride, stride));
	gridRct.setOutlineColor(sf::Color::White);
	gridRct.setOutlineThickness(0.9f);
	gridRct.setFillColor(sf::Color::Transparent);
}

void Game::initMainMenu()
{
	mainMenu = new Menu(4);
	setMainMenuButtons();
	mainMenu->audioManagerRef = &this->audioManager;
}

void Game::setMainMenuButtons()
{
	mainMenu->setSelectable(0, "Play", sf::Vector2f(WIDTH / 2, HEIGHT / (mainMenu->itemNumbers + 1) * 1));
	mainMenu->setSelectable(1, "Load Game", sf::Vector2f(WIDTH / 2, HEIGHT / (mainMenu->itemNumbers + 1) * 2));
	mainMenu->setSelectable(2, "Options", sf::Vector2f(WIDTH / 2, HEIGHT / (mainMenu->itemNumbers + 1) * 3));
	mainMenu->setSelectable(3, "Exit", sf::Vector2f(WIDTH / 2, HEIGHT / (mainMenu->itemNumbers + 1) * 4 - 20));
	mainMenu->setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
}

void Game::initPauseMenu()
{
	pauseMenu = new Menu(3);
	setPauseMenuButtons();
	pauseMenu->audioManagerRef = &this->audioManager;
}

void Game::setPauseMenuButtons()
{
	pauseMenu->setSelectable(0, "Continue", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y - 200));
	pauseMenu->setSelectable(1, "Options", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y));
	pauseMenu->setSelectable(2, "Main Menu", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y + 200));
	pauseMenu->setPosition(sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y));
}

void Game::initGameOverMenu()
{
	gameOverMenu = new Menu();
	setGameOverMenuButtons();
	gameOverMenu->audioManagerRef = &this->audioManager;
}

void Game::setGameOverMenuButtons()
{
	gameOverMenu->setSelectable(0, "Retry", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y - 100));
	gameOverMenu->setSelectable(1, "Main Menu", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y + 100));
	gameOverMenu->setPosition(sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y));
}

void Game::initWinMenu()
{
	winMenu = new Menu();
	setWinMenuButtons();
	winMenu->audioManagerRef = &this->audioManager;
}

void Game::setWinMenuButtons()
{
	winMenu->setSelectable(0, "Play Again", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y - 100));
	winMenu->setSelectable(1, "Main Menu", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y + 100));
	winMenu->setPosition(sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y));
}

void Game::initOptionsMenu()
{
	optionsMenu = new Menu(3);
	setOptionsMenuButtons();
	optionsMenu->audioManagerRef = &this->audioManager;	
}

void Game::setOptionsMenuButtons()
{
	std::string vol = "Music Volume : \n" + std::to_string(audioManager.musicVolume);
	optionsMenu->setSelectable(0, vol, sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y - 50));
	vol = "SFX Volume : \n" + std::to_string(audioManager.sfxVolume);
	optionsMenu->setSelectable(1, vol, sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y + 50));
	optionsMenu->setSelectable(2, "Back", sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y + 200));
	optionsMenu->setPosition(sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y));
}

void Game::loadMainMenu()
{
	initMainMenu();
	initOptionsMenu();
}

void Game::unloadMainMenu()
{
	delete(mainMenu);
}

void Game::loadGame()
{
	this->initFonts();
	this->initWorld();
	this->initPlayer();
	this->initGrid();
	this->initPauseMenu();

	world->worldInitialized = true;

	world->loadMap();
	charactersManager->loadCharacters();

	savePlayerDataInSave();
	charactersManager->saveCharactersInSave();
}

void Game::loadGameFromSave()
{
	this->initFonts();
	this->initWorld();
	this->initPlayer();
	this->initGrid();
	this->initPauseMenu();

	world->worldInitialized = true;

	world->loadMap();
	charactersManager->loadCharactersFromSave();
	loadPlayerDataFromSave();
	player->moved = true;
	this->moveCamera((player->cx + player->rx) * stride, (player->cy + player->ry) * stride);
}

void Game::unloadGame()
{
	delete(world);
	delete(player);
	delete(winMenu);
	delete(gameOverMenu);
	delete(pauseMenu);
	enemiesList.clear();
}

void Game::pressSelectedButton()
{
	switch (GS)
	{
		case Game::GameState::MainMenu:
			if (currentMenu->getSelectedButton() == "Play")
			{
				loadSave = false;
				setGameState(GameState::InGame);
				return;
			}
			else if (currentMenu->getSelectedButton() == "Load Game")
			{
				loadSave = true;
				setGameState(GameState::InGame);
				return;
			}
			else if (currentMenu->getSelectedButton() == "Exit")
			{
				closeWindow();
				return;
			}
			pressSelectedButtonOptions();
			break;
		
		case Game::GameState::Pause:
			if (currentMenu->getSelectedButton() == "Continue")
			{
				setGameState(GameState::InGame);
				return;
			}
			else if (currentMenu->getSelectedButton() == "Back")
			{
				currentMenu = pauseMenu;
				return;
			}
			else if (currentMenu->getSelectedButton() == "Main Menu")
			{
				setGameState(GameState::MainMenu);
				return;
			}
			pressSelectedButtonOptions();
			break;
		
		case Game::GameState::GameOver:
			if (currentMenu->getSelectedButton() == "Retry")
			{
				loadSave = true;
				setGameState(GameState::InGame);
				return;
			}
			else if (currentMenu->getSelectedButton() == "Main Menu")
			{
				setGameState(GameState::MainMenu);
				return;
			}
			break;
		
		case Game::GameState::Win:
			if (currentMenu->getSelectedButton() == "Play Again")
			{
				loadSave = false;
				setGameState(GameState::InGame);
				return;
			}
			else if (currentMenu->getSelectedButton() == "Main Menu")
			{
				setGameState(GameState::MainMenu);
				return;
			}
			break;
		
		case Game::GameState::Cinematic:
			break;
		
		default:
			break;
	}
}

void Game::pressSelectedButtonOptions()
{
	if (currentMenu->getSelectedButton() == "Options")
	{
		currentMenu = optionsMenu;
	}
	else if (currentMenu->getSelectedButton().find("Music Volume") == 0)
	{
		audioManager.changeMusicVolume(audioManager.musicVolume + audioManager.musicVolumeModifier);
		if (audioManager.musicVolume > 100)		
			audioManager.changeMusicVolume(0);
		setOptionsMenuButtons();
	}
	else if (currentMenu->getSelectedButton().find("SFX Volume") == 0)
	{
		audioManager.sfxVolume += audioManager.sfxVolumeModifier;
		if (audioManager.sfxVolume > 100)
			audioManager.sfxVolume = 0;
		setOptionsMenuButtons();
	}
	else if (currentMenu->getSelectedButton() == "Back")
	{
		currentMenu = mainMenu;
	}
}

#pragma endregion

Game::Game()
{
	this->initWindow();
	this->initMusic();	
	sf::Listener::setDirection(0.f, 0.f, -1.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);

	saveSound = new sf::SoundBuffer();
	if (!saveSound->loadFromFile("Assets/Sounds/save.wav"))
		printf("Save sound could not be loaded from Assets/Sounds/save.wav");

	loadMainMenu();
	currentMenu = mainMenu;
	mouseShape = SetCircle(3, sf::Color::Magenta, getMousePosition());


	//tmp
	sf::err().rdbuf(NULL);
}

Game::~Game()
{
}

void Game::update()
{
	if (pastMousePos != (sf::Vector2i)getMousePosition())
	{
		mouseShape.setPosition(getMousePosition());
		if (currentMenu != nullptr)
			isMouseOverButton = currentMenu->manageMouse((sf::Vector2i)getMousePosition());
		pastMousePos = (sf::Vector2i)getMousePosition();
	}

	//dt
	elapsedTime = clock.restart();
	dt = elapsedTime.asSeconds();

	joystickMenuSelection_TIMER -= dt;

	//updates
	switch (GS)
	{
		case Game::GameState::InGame:
			if (world->worldInitialized)
			{
				player->update(dt);
				charactersManager->update(dt);
				checkIfPlayerTouchCheckpoint();
				if (checkIfPlayerEntersInWinZone())
					setGameState(GameState::Win);
			}
			break;
	}

	//events
	while (this->window.pollEvent(this->gameEvent))
	{
		ImGui::SFML::ProcessEvent(this->gameEvent);
		switch (gameEvent.type)
		{
			case sf::Event::Closed:
				closeWindow();
				break;

			case sf::Event::KeyPressed:
				checkPressedKey(this->gameEvent.key.code);
				break;

			case sf::Event::KeyReleased:
				checkReleasedKey(this->gameEvent.key.code);
				break;

			case sf::Event::JoystickButtonPressed:
				checkPressedJoystic(this->gameEvent.joystickButton);
				break;

			case sf::Event::JoystickButtonReleased:
				checkReleasedJoystic(this->gameEvent.joystickButton);
				break;

			case sf::Event::MouseButtonPressed:
				checkPressedMouse(gameEvent.key.code);
				break;

			case sf::Event::JoystickMoved:
				checkJoysticAxis(gameEvent.joystickMove.axis);
				break;

		}
	}
	//ImGui
	this->processImGui();
}

void Game::checkPressedKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
			if (GS == GameState::InGame)
				setGameState(GameState::Pause);
			else if (GS == GameState::Pause)
				setGameState(GameState::InGame);
			break;

		case sf::Keyboard::Space:
			if (GS == GameState::InGame)
				player->manageEventInputs(key);
			break;

		case sf::Keyboard::Up:
			if (GS != GameState::InGame)
				currentMenu->moveUp();
			break;

		case sf::Keyboard::Down:
			if (GS != GameState::InGame)
				currentMenu->moveDown();
			break;

		case sf::Keyboard::Return:
			if (GS != GameState::InGame)
				pressSelectedButton();
			break;

		default:
			break;
	}
}

void Game::checkReleasedKey(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Space:
			if (GS == GameState::InGame)
				player->manageEventInputsRelease(key);
			break;
	}
}

void Game::checkPressedMouse(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Mouse::Left:
			if (isMouseOverButton && currentMenu != nullptr)
				pressSelectedButton();

			if (GS != GameState::MainMenu)
			{
				if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
				{
					if (strcmp(selectedEntity, "wall") == 0)
					{
						sf::Vector2f mousePosition = getMousePosition();
						world->placeWall(mousePosition.x / stride, mousePosition.y / stride);
					}
					else if (strcmp(selectedEntity, "deathZone") == 0)
					{
						sf::Vector2f mousePosition = getMousePosition();
						world->placeDeathZone(mousePosition.x / stride, mousePosition.y / stride);
					}
					else if (strcmp(selectedEntity, "checkpoint") == 0)
					{
						sf::Vector2f mousePosition = getMousePosition();
						world->placeCheckPoint(mousePosition.x / stride, mousePosition.y / stride);
					}
					else if (strcmp(selectedEntity, "winzone") == 0)
					{
						sf::Vector2f mousePosition = getMousePosition();
						world->placeWinZone(mousePosition.x / stride, mousePosition.y / stride);
					}
				}
			}
		break;
	}
}

void Game::checkPressedJoystic(sf::Event::JoystickButtonEvent buttonEvent)
{
	switch (buttonEvent.button)
	{
		case ControllerButtons::south:
			if (GS != GameState::InGame)
				pressSelectedButton();
			break;

		case ControllerButtons::start:
			if (GS == GameState::InGame)
				setGameState(GameState::Pause);
			else if (GS == GameState::Pause)
				setGameState(GameState::InGame);
			break;
	}
}

void Game::checkReleasedJoystic(sf::Event::JoystickButtonEvent buttonEvent)
{
	player->manageEventJoystickRelease(buttonEvent);
}

void Game::checkJoysticAxis(sf::Joystick::Axis axis)
{
	float amount = gameEvent.joystickMove.position;
	switch (axis)
	{
		case sf::Joystick::Y:
			if (amount > controllerDeadZone || amount < -controllerDeadZone)
				if (GS != GameState::InGame)
				{
					if (joystickMenuSelection_TIMER <= 0)
					{
						if (amount > 50)
						{
							currentMenu->moveUp();
							joystickMenuSelection_TIMER = joystickMenuSelection_CD;
						}
						else if (amount < -50)
						{
							currentMenu->moveDown();
							joystickMenuSelection_TIMER = joystickMenuSelection_CD;
						}
					}
				}
			break;

		case sf::Joystick::PovY:
			if (amount > controllerDeadZone || amount < -controllerDeadZone)
				if (GS != GameState::InGame)
				{
					if (amount > 0)
						currentMenu->moveUp();
					else
						currentMenu->moveDown();
				}
			break;
	}
}

void Game::processImGui()
{
	bool toolActive;
	ImGui::SFML::Update(window, elapsedTime);

	ImGui::Begin("Tools", &toolActive, ImGuiWindowFlags_MenuBar);

	if (GS != GameState::MainMenu)
	{
		if (imIdx == 0)
		{
			ImGui::Value("FPS ", 1.0f / dt);
			ImGui::Checkbox("Debug mouse", &debugMouse);
			if (debugMouse)
			{
				sf::Vector2f mousePos = getMousePosition();
				ImGui::Text("Mouse : { x%0.0f y%0.0f }", mousePos.x, mousePos.y);
				ImGui::Text("Mouse cell : { x%0.0f y%0.0f }", mousePos.x / stride, mousePos.y / stride);
				float rad = mouseShape.getRadius();
				if (ImGui::SliderFloat("Shape size", &rad, 1, 10))
					mouseShape.setRadius(rad);
			}
			if (ImGui::DragFloat("Gravity", &gravity, 0.05f, -5, 5))
			{
				world->gravity = this->gravity;
			}

			float vol = audioManager.musicVolume;
			if (ImGui::DragFloat("Volume", &vol, 1, 0, 100))
			{
				audioManager.changeMusicVolume(vol);

			}
		}
		else if (imIdx == 1)
		{
			if (ImGui::TreeNode("Existing characters"))
			{
				int idx = 0;

				charactersImGui((Character*)player, idx, true);

				enemiesList = charactersManager->getEnemiesList();
				for (Character* c : enemiesList)
				{
					ImGui::PushID(idx);

					charactersImGui(c, idx);

					idx++;
					ImGui::PopID();
				}

				ImGui::Spacing();

				if (ImGui::TreeNode("Create new"))
				{
					static char name[20] = "";
					ImGui::InputText("Name", name, 20);
					static int pos[2] = { 1,1 };
					ImGui::DragInt2("Pos", pos, 1, 0, 100);
					static int health = 100;
					ImGui::DragInt("Health", &health, 1, 0, 1000);
					static int selectedIdx = 0;
					static sf::Texture* selectedTexture = charactersManager->textures[selectedIdx];
					if (ImGui::Combo("Textures", &selectedIdx, charactersManager->texturesNames, IM_ARRAYSIZE(charactersManager->texturesNames)))
					{
						selectedTexture = charactersManager->textures[selectedIdx];
					}
					if (ImGui::Button("+"))
					{
						Enemy* c = new Enemy(name, pos[0], pos[1], stride, *selectedTexture);
						if (health > 0)
							c->currentHealth = c->maxHealth = health;
						c->setWorld(world);
						c->audioManagerRef = &this->audioManager;
						c->setPlayer(player);
						c->setGravity(gravity);
						charactersManager->addEnemy(c);
					}
					ImGui::TreePop();
				}

				ImGui::TreePop();
			}
		}
		else if (imIdx == 2)
		{
			static int entityIdx = 0;
			if (ImGui::Combo("Place Entity", &entityIdx, entities, IM_ARRAYSIZE(entities)))
			{
				selectedEntity = entities[entityIdx];
			}
			ImGui::Checkbox("Draw grid", &renderGrid);
			if (renderGrid)
			{
				ImGui::DragFloat("Grid X", &gridSize.x, 1, 0);
				ImGui::DragFloat("Grid Y", &gridSize.y, 1, 0);
			}
		}


		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::TreeNode("Map"))
				{
					if (ImGui::Button("Save"))
					{
						this->world->saveMapInFile();
					}
					ImGui::Spacing();
					if (ImGui::Button("Load"))
					{
						this->world->loadMap();
					}
					ImGui::Spacing();
					if (ImGui::TreeNode("Erase"))
					{
						if (ImGui::Button("Really ?"))
						{
							this->world->eraseMap();
						}
						ImGui::TreePop();
					}
					ImGui::Spacing();
					ImGui::TreePop();
				}
				ImGui::Separator();
				if (ImGui::TreeNode("Characters"))
				{
					if (ImGui::Button("Save"))
					{
						this->charactersManager->saveCharactersInFile();
					}
					ImGui::Spacing();
					if (ImGui::Button("Load"))
					{
						this->charactersManager->loadCharacters();
					}
					ImGui::Spacing();
					if (ImGui::TreeNode("Erase"))
					{
						if (ImGui::Button("Really ?"))
						{
							this->charactersManager->killAll();
						}
						ImGui::TreePop();
					}
					ImGui::Spacing();
					ImGui::TreePop();
				}
				ImGui::Separator();
				if (ImGui::TreeNode("Player"))
				{
					if (ImGui::Button("Save"))
					{
						this->savePlayerDataInFile();
					}
					ImGui::Spacing();
					if (ImGui::Button("Load"))
					{
						this->loadPlayerDataInFile();
					}
					ImGui::Spacing();
					ImGui::TreePop();
				}


				ImGui::EndMenu();
			}
			if (ImGui::Button("General"))
				imIdx = 0;
			if (ImGui::Button("Characters"))
				imIdx = 1;
			if (ImGui::Button("Map"))
				imIdx = 2;
			ImGui::EndMenuBar();
		}
	}

	ImGui::End();
}
void Game::charactersImGui(Character* chara, int idx, bool isPlayer)
{
	static float d;

	if (ImGui::TreeNode(chara->name.c_str()))
	{
		ImGui::Text("Health : %f / %f", chara->currentHealth, chara->maxHealth);

		if (ImGui::Button("Damage"))
		{
			if (isPlayer)
				player->takeDamages(d);
			else
			{
				chara->takeDamages(d);
				if (chara->currentHealth <= 0)
					charactersManager->enemies.erase(charactersManager->enemies.begin() + idx);
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Heal"))
			if (isPlayer)
				player->heal(d);
			else
				chara->heal(d);

		ImGui::SameLine();
		ImGui::DragFloat("amount", &d, 1.0f, 0, 200);
		switch (chara->characterState)
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
		if (ImGui::TreeNode("Position"))
		{
			ImGui::Text("Pos : {x%d y%d}", chara->cx, chara->cy);
			ImGui::Text("Mov : {x%.1f y%.1f}", chara->dx, chara->dy);
			chara->moved |= (ImGui::DragInt("cx", &chara->cx, 1));
			chara->moved |= (ImGui::DragInt("cy", &chara->cy, 1));
			chara->moved |= (ImGui::DragFloat("rx", &chara->rx, 0.05f));
			chara->moved |= (ImGui::DragFloat("ry", &chara->ry, 0.05f));

			ImGui::TreePop();
		}
		ImGui::Separator();

		ImGui::TreePop();
	}
}

void Game::moveCamera(float x, float y)
{
	this->mainView->setCenter(x, y);
	this->window.setView(*mainView);
}

bool Game::checkIfBulletHitsEnemy(int _cx, int _cy, float damages, int knockbackForce)
{
	for (int i = 0; i < charactersManager->enemies.size(); i++)
	{
		if (charactersManager->enemies[i]->alive())
		{
			if (charactersManager->enemies[i]->cx == _cx && charactersManager->enemies[i]->cy == _cy)
			{
				charactersManager->enemies[i]->takeDamages(damages, _cx * stride, _cy * stride, knockbackForce);
				return true;
			}
		}
	}
	return false;
}

bool Game::checkIfPlayerTouchCheckpoint()
{
	for (auto cp : world->checkpoints)
	{
		if (!cp->isActivated())
		{
			if (cp->cx == player->cx && cp->cy == player->cy)
			{
				cp->setActive(true);
				world->lastActivatedCheckpoint = cp;
				savePlayer(playerSavedDataPath);
				charactersManager->saveCharactersInSave();
				audioManager.playSound(saveSound);

				player->heal(cp->getHealAmount());
				return true;

			}
		}
	}
	return false;
}

bool Game::checkIfPlayerEntersInWinZone()
{
	if (player->cx == world->winzone->cx && player->cy == world->winzone->cy)
		return true;

	return false;
}

void Game::savePlayer(const char* filePath)
{
	FILE* f = nullptr;
	fopen_s(&f, filePath, "wb");
	if (f)
	{
		std::string playerData = "";

		if (world->lastActivatedCheckpoint != nullptr)
			playerData += std::to_string(world->lastActivatedCheckpoint->cx) + " " + std::to_string(world->lastActivatedCheckpoint->cy) + " " + std::to_string(player->currentHealth) + "\n";
		else
			playerData += std::to_string(player->cx) + " " + std::to_string(player->cy) + " " + std::to_string(player->currentHealth) + "\n";

		fprintf(f, playerData.c_str());

		fflush(f);
		fclose(f);
	}
}

void Game::loadPlayer(const char* filePath)
{
	FILE* f = nullptr;
	fopen_s(&f, filePath, "rb");
	if (f)
	{
		int64_t _cx = 0;
		int64_t _cy = 0;
		int64_t _currentHealth = 0;
		fscanf_s(f, "%lld %lld %lld\n", &_cx, &_cy, &_currentHealth);
		player->cx = _cx;
		player->cy = _cy;
		player->currentHealth = _currentHealth;

		fclose(f);
	}
}

void Game::savePlayerDataInFile()
{
	savePlayer(playerDataPath);
}

void Game::loadPlayerDataInFile()
{
	loadPlayer(playerDataPath);
}

void Game::savePlayerDataInSave()
{
	savePlayer(playerSavedDataPath);
}

void Game::loadPlayerDataFromSave()
{
	loadPlayer(playerSavedDataPath);
}

void Game::drawGrid()
{
	for (int y = 0; y < gridSize.y * stride; y += stride) 
	{
		for (int x = 0; x < gridSize.x * stride; x += stride) 
		{
			gridRct.setPosition(x + stride, y + stride);
			window.draw(gridRct);
		}
	}
}

void Game::render()
{
	this->window.clear();

	if (debugMouse)
		window.draw(mouseShape);


	switch (GS)
	{
		case Game::GameState::MainMenu:
			break;

		case Game::GameState::InGame:
			renderWorldAndCharacters();
			break;

		case Game::GameState::Pause:
			renderWorldAndCharacters();
			this->window.draw(stateText);
			break;

		case Game::GameState::GameOver:
			renderWorldAndCharacters();
			this->window.draw(stateText);
			break;

		case Game::GameState::Win:
			renderWorldAndCharacters();
			this->window.draw(stateText);
			break;

		case Game::GameState::Cinematic:
			break;

		default:
			break;
	}

	if (currentMenu != nullptr)
		currentMenu->render(this->window);

	ImGui::SFML::Render(window);

	this->window.display();
}

void Game::renderWorldAndCharacters()
{
	this->world->render(this->window);
	this->charactersManager->render(this->window);

	this->player->render(this->window);

	if (renderGrid)
		drawGrid();
}

float Game::deltaTime()
{
	return this->dt;
}

World* Game::getWorld()
{
	return this->world;
}

sf::RenderWindow& Game::getWindow()
{
	return this->window;
}

sf::Vector2f Game::getMousePosition()
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(this->window), *mainView);
}

void Game::setGameState(GameState _GS)
{
	switch (_GS)
	{
		case Game::GameState::MainMenu:
			audioManager.setMusic("Assets/Sounds/mainmenu.ogg");
			moveCamera(WIDTH / 2, HEIGHT / 2);
			loadMainMenu();
			currentMenu = mainMenu;
			unloadGame();
			break;

		case Game::GameState::InGame:
			if (GS != GameState::Pause)
			{
				if (loadSave)
					loadGameFromSave();
				else
					loadGame();
				audioManager.setMusic("Assets/Sounds/maintheme.ogg");
			}
			currentMenu = nullptr;
			deactivateStateText();
			break;

		case Game::GameState::Pause:
			if (pauseMenu == nullptr)
				initPauseMenu();
			else
			{
				setPauseMenuButtons();
				setOptionsMenuButtons();
			}
			activateStateText("Pause");
			currentMenu = pauseMenu;
			break;

		case Game::GameState::GameOver:
			if (gameOverMenu == nullptr)
				initGameOverMenu();
			else
				setGameOverMenuButtons();

			activateStateText("Vous mort");
			currentMenu = gameOverMenu;
			break;

		case Game::GameState::Win:
			audioManager.playWinMusic();
			if (winMenu == nullptr)
				initWinMenu();
			else
				setWinMenuButtons();

			activateStateText("Vous gagnant");
			currentMenu = winMenu;
			break;

		case Game::GameState::Cinematic:
			break;

		default:
			break;
	}
	this->GS = _GS;
}

void Game::activateStateText(std::string text)
{
	stateText.setOrigin(stateText.getGlobalBounds().width / 2, stateText.getGlobalBounds().height / 2);
	stateText.setPosition(mainView->getCenter().x, mainView->getCenter().y - 420);
	stateText.setFillColor(sf::Color::Yellow);
	stateText.setOutlineColor(sf::Color::White);

	if (text != "")
		stateText.setString(text);
}

void Game::deactivateStateText()
{
	stateText.setFillColor(sf::Color::Transparent);
	stateText.setOutlineColor(sf::Color::Transparent);
}
