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
	mainMenu = new Menu();
	mainMenu->setSelectable(0, "Play", sf::Vector2f(WIDTH / 2.1f, HEIGHT / (mainMenu->itemNumbers + 1) * 1));
	mainMenu->setSelectable(1, "Exit", sf::Vector2f(WIDTH / 2.1f, HEIGHT / (mainMenu->itemNumbers + 1) * 2));
	mainMenu->setBox(sf::Color::Green, sf::Vector2f(WIDTH / 2, HEIGHT / 2), sf::Vector2f(300, 500));
	mainMenu->audioManagerRef = &this->audioManager;
}

void Game::initPauseMenu()
{
	pauseMenu = new Menu();
	pauseMenu->setSelectable(0, "Continue", sf::Vector2f(WIDTH / 2, HEIGHT / (pauseMenu->itemNumbers + 1) * 1));
	pauseMenu->setSelectable(1, "Main Menu", sf::Vector2f(WIDTH / 2, HEIGHT / (pauseMenu->itemNumbers + 1) * 2));
	pauseMenu->setBox(sf::Color::Green, sf::Vector2f(WIDTH / 2, HEIGHT / 2), sf::Vector2f(300, 500));
	pauseMenu->audioManagerRef = &this->audioManager;
}

void Game::loadMainMenu()
{
	initMainMenu();
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
}

void Game::unloadGame()
{
	delete(world);
	delete(player);
	enemiesList.clear();
}

void Game::pressSelectedButton()
{
	switch (GS)
	{
		case Game::MainMenu:
			if (mainMenu->getSelectedButton() == "Play")
			{
				setGameState(GameState::InGame);
			}
			else if (mainMenu->getSelectedButton() == "Exit")
			{
				closeWindow();
			}
			break;
		
		case Game::Pause:
			if (pauseMenu->getSelectedButton() == "Continue")
			{
				setGameState(GameState::InGame);
			}
			else if (pauseMenu->getSelectedButton() == "Main Menu")
			{
				setGameState(GameState::MainMenu);
			}
			break;
		
		case Game::GameOver:
			break;
		
		case Game::Win:
			break;
		
		case Game::Cinematic:
			break;
		
		default:
			break;
	}
}

#pragma endregion

Game::Game()
{
	this->initWindow();
	this->initMusic();	
	sf::Listener::setDirection(0.f, 0.f, -1.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
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
	mouseShape.setPosition(getMousePosition());
	//dt
	elapsedTime = clock.restart();
	dt = elapsedTime.asSeconds();


	//updates
	switch (GS)
	{
		case Game::MainMenu:
			break;

		case Game::InGame:
			if (world->worldInitialized)
			{
				player->update(dt);
				charactersManager->update(dt);
			}
			break;

		case Game::Pause:
			break;

		case Game::GameOver:
			break;

		case Game::Win:
			break;

		case Game::Cinematic:
			break;

		default:
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
			if (GS == GameState::MainMenu)
				mainMenu->moveUp();
			if (GS == GameState::Pause)
				pauseMenu->moveUp();
			break;

		case sf::Keyboard::Down:
			if (GS == GameState::MainMenu)
			{
				mainMenu->moveDown();
			}
			if (GS == GameState::Pause)
			{
				pauseMenu->moveUp();

			}
			break;

		case sf::Keyboard::Return:
			if (GS != GameState::InGame)
				pressSelectedButton();

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
					if (amount > 0)
						currentMenu->moveUp();
					else
						currentMenu->moveDown();
				}
			break;

		case sf::Joystick::Z:
			if (amount > controllerDeadZone || amount < -controllerDeadZone)
				player->fireWeapon();
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
					static int health = 5;
					ImGui::DragInt("Health", &health, 1, 0, 100);
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
			ImGui::Checkbox("Show Death Zones", &world->renderDeathZones);
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
		ImGui::DragFloat("amount", &d, 0.5f, 0, 10);
		ImGui::Value("State", (Character::State)chara->characterState);
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


bool Game::checkIfBulletHitsEnemy(int _cx, int _cy, float damages)
{
	for (int i = 0; i < charactersManager->enemies.size(); i++)
	{
		if (charactersManager->enemies[i]->cx == _cx && charactersManager->enemies[i]->cy == _cy)
		{
			charactersManager->enemies[i]->takeDamages(damages);
			return true;
		}
	}
	return false;
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
		case Game::MainMenu:
			this->mainMenu->render(this->window);
			break;

		case Game::InGame:
			renderWorldAndCharacters();
			break;

		case Game::Pause:
			renderWorldAndCharacters();
			pauseMenu->render(this->window);
			this->window.draw(stateText);
			break;

		case Game::GameOver:
			renderWorldAndCharacters();
			this->window.draw(stateText);
			break;

		case Game::Win:
			renderWorldAndCharacters();
			this->window.draw(stateText);
			break;

		case Game::Cinematic:
			break;

		default:
			break;
	}

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
		case Game::MainMenu:
			audioManager.setMusic("Assets/Sounds/mainmenu.ogg");
			moveCamera(WIDTH / 2, HEIGHT / 2);
			loadMainMenu();
			currentMenu = mainMenu;
			unloadGame();
			break;

		case Game::InGame:
			if (GS == GameState::MainMenu)
			{
				loadGame();
				audioManager.setMusic("Assets/Sounds/maintheme.ogg");
				unloadMainMenu();
			}
			deactivateStateText();
			break;

		case Game::Pause:
			pauseMenu->setSelectable(0, "Continue", sf::Vector2f(mainView->getCenter().x - 50, mainView->getCenter().y - 100));
			pauseMenu->setSelectable(1, "Main Menu", sf::Vector2f(mainView->getCenter().x - 50, mainView->getCenter().y  + 100));
			pauseMenu->setBox(sf::Color::Green, sf::Vector2f(mainView->getCenter().x, mainView->getCenter().y), sf::Vector2f(300, 500));
			activateStateText("Pause");
			currentMenu = pauseMenu;
			break;

		case Game::GameOver:
			activateStateText("Vous mort");
			break;

		case Game::Win:
			activateStateText("Vous gagnant");
			break;

		case Game::Cinematic:
			break;

		default:
			break;
	}
	this->GS = _GS;
}

void Game::activateStateText(std::string text)
{
	stateText.setPosition(mainView->getCenter().x - 150, mainView->getCenter().y - 400);
	stateText.setFillColor(sf::Color::Yellow);
	stateText.setOutlineColor(sf::Color::White);

	if (text != "")
		stateText.setString(text);
}

void Game::deactivateStateText()
{
	stateText.setFillColor(sf::Color::Transparent);
	stateText.setFillColor(sf::Color::Transparent);
}
