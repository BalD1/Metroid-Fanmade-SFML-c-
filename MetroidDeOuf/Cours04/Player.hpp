#pragma once
#include "Character.hpp"
#include "Weapon.hpp"
#include "AudioManager.hpp"
#include <map>

class Game;

class Player : public Character, public sf::Transform
{
private:
	//vars

	const char*				normalFormTexturePath = "Assets/Graphs/samusnormal.png";
	const char*				ballFormTexturePath = "Assets/Graphs/samusball.png";

	bool					isFacingRight = true;

	Weapon*					currentWeapon = nullptr;

	sf::RenderStates		states;

	float					jumpForce = 15;
	float					jumpLength = 0.5f;
	float					jumpTimer = 0;

	float					dt = 0;

	bool					canJump = true;

	bool					isInNormalForm = true;

	sf::Texture*			normalTexture = nullptr;
	sf::Texture*			ballTexture = nullptr;

	sf::Texture*			barHolderTexture = nullptr;
	sf::Texture*			barTexture = nullptr;
	sf::Sprite*				barHolder = nullptr;
	sf::Sprite*				bar = nullptr;

	sf::Vector2f			barOffset = { -750,-440 };

	sf::SoundBuffer*		jumpSound = nullptr;
	sf::SoundBuffer*		hurtSound = nullptr;
	sf::SoundBuffer*		deathSound = nullptr;


	//funcs

public:

	//vars

	std::map<char, int>		inventory =
	{
		{'ball', 0},
	};

	float				joystickDeadZone = 20;
	Game*				gameRef = nullptr;


	//funcs

	Player(std::string _name, int _cx, int _cy, int _stride);
	Player(std::string _name, float _speed, float _invicibilityCD, float _maxHealth, int _cx, int _cy, int _stride);
	~Player();

	void initSprite();
	void initWeapon();
	void initHPBar();
	void initSounds();

	void setGame(Game* _gameRef);
	void setWorld(World* _worldRef);
	void setAudioManager(AudioManager* _audiomanagerRef);

	void im();

	void render(sf::RenderTarget& target);
	void update(float dt);

	void manageInputs();
	void manageEventInputs(sf::Keyboard::Key key);
	void manageEventInputsRelease(sf::Keyboard::Key key);
	void manageEventAxis(sf::Joystick::Axis axis, float amount);
	void manageEventJoystickRelease(sf::Event::JoystickButtonEvent buttonEvent);

	void fireWeapon();

	void jump();
	void jumpBehaviour();

	void checkIfInDeathZone();
	void takeDamages(int rawDamages, int otherXX = 0, int otherYY = 0, int _knockbackForce = 0);
	void heal(float rawHeal);
	void kill();

	void flipSprite();

	void changeForm();

};

