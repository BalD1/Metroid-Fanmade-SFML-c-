#pragma once
#include "stdafx.hpp"
#include "AudioManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Character.hpp"
#include "World.hpp"

class Game
{
private:

	// vars

	sf::RenderWindow			window;
	sf::View*					mainView;
	sf::Event					gameEvent;

	const int					WIDTH = 1600;
	const int					HEIGHT = 900;

	sf::Font					titleFont;
	sf::Font					baseFont;
	sf::Text					stateText;

	sf::RectangleShape			gridRct;
	sf::Vector2f				gridSize = { 25,25 };
	bool						renderGrid = false;

	bool						debugMouse = false;

	sf::CircleShape				mouseShape;

	sf::Clock					clock;
	sf::Time					elapsedTime;
	float						dt = 0;

	AudioManager				audioManager;

	sf::Texture*				textures[2];
	const char*					texturesNames[2] = { "redTexture", "purpleTexture"};
	const char*					entities[3] = {"none", "wall", "deathZone"};
	const char*					selectedEntity = "";
	std::vector<Enemy*>			enemiesList;

	World*						world;

	int							imIdx = 0;

	// funcs

	void initWindow();
	void initFonts();
	void closeWindow();
	void initMusic();
	void initPlayer();
	void initWorld();
	void initEnemies();
	void initGrid();

public:

	// vars

	Player*						player;

	sf::Vector2f				windowSize;
	sf::Vector2f				windowCenter;

	int							stride = 32;

	float						gravity = 2.976;

	enum						GameState
	{
		MainMenu,
		InGame,
		Pause,
		GameOver,
		Win,
		Cinematic,
	};
	GameState					GS = MainMenu;

	// funcs

	Game();
	~Game();


	void update();

	bool checkIfBulletHitsEnemy(int _cx, int _cy, float damages);

	// keys managers
	void checkPressedKey(sf::Keyboard::Key key);
	void checkReleasedKey(sf::Keyboard::Key key);
	void checkPressedMouse(sf::Keyboard::Key key);

	// imgui
	void processImGui();
	void charactersImGui(Character* chara, int idx, bool isPlayer = false);

	// renderers
	void moveCamera(float x, float y);
	void drawGrid();
	void render();

	// dt
	float deltaTime();

	// gets
	World* getWorld();
	sf::RenderWindow& getWindow();
	sf::Vector2f getMousePosition();

	// sets
	void setGameState(GameState _GS);

};

