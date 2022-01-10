#pragma once
#include "Character.hpp"
#include "Weapon.hpp"
#include "AudioManager.hpp"

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

	sf::SoundBuffer*	jumpSound = nullptr;
	sf::SoundBuffer*	hurtSound = nullptr;

	//funcs

public:

	//vars

	float				joystickDeadZone = 20;
	Game*				gameRef = nullptr;


	//funcs

	Player(std::string _name, float _cx, float _cy, int _stride);
	Player(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, float _cx, float _cy, int _stride);
	~Player();

	void initSprite();
	void initWeapon();
	void initHPBar();
	void initSounds();

	void setGame(Game* _gameRef);
	void setWorld(World* _worldRef);

	void im();

	void render(sf::RenderTarget& target);
	void update(float dt);

	void manageInputs();
	void manageEventInputs(sf::Keyboard::Key key);
	void manageEventInputsRelease(sf::Keyboard::Key key);
	void manageEventJoystickRelease(sf::Event::JoystickButtonEvent buttonEvent);

	void fireWeapon();

	void jump();
	void jumpBehaviour();

	void checkIfInDeathZone();
	void takeDamages(float rawDamages, int otherXX = 0, int otherYY = 0, int _knockbackForce = 0);
	void kill();

};

