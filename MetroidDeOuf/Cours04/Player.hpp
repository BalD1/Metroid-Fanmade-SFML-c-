#pragma once
#include "Character.hpp"
#include "Weapon.hpp"

class Game;

class Player : public Character, public sf::Transform
{
private:
	//vars

	Weapon*				currentWeapon = nullptr;

	sf::RenderStates	states;

	float				jumpForce = 20;
	float				jumpLength = 0.5f;
	float				jumpTimer = 0;

	float				dt = 0;

	bool				canJump = true;

	sf::Texture*		barHolderTexture = nullptr;
	sf::Texture*		barTexture = nullptr;
	sf::Sprite*			barHolder = nullptr;
	sf::Sprite*			bar = nullptr;

	sf::Vector2f		barOffset = { -750,-440 };

	//funcs

public:

	//vars

	Game*				gameRef = nullptr;


	//funcs

	Player(std::string _name, float _cx, float _cy, int _stride);
	Player(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride);
	~Player();

	void initSprite();
	void initWeapon();
	void initHPBar();

	void setGame(Game* _gameRef);
	void setWorld(World* _worldRef);

	void im();

	void render(sf::RenderTarget& target);
	void update(float dt);

	void manageInputs();
	void manageEventInputs(sf::Keyboard::Key key);
	void manageEventInputsRelease(sf::Keyboard::Key key);
	void jump();
	void jumpBehaviour();

	void checkIfInDeathZone();
	void takeDamages(float rawDamages);
	void kill();

};

