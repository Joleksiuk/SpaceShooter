#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

using namespace sf;
class Player
{
private:
	Sprite sprite;
	Texture texture;
	
	
	//game logic
	int hp;
	int points;
	int movementSpeed;
	int attackPower;
	float attackCooldown;
	float attackCooldownMax;

	//private functions
	void initTexture();
	void initSprite(float &resolutionModifier);
	void initVariables();
	
public:
	Player(float &resolutionModifier);
	virtual ~Player();

	//Accessors
	const FloatRect& getBounds() const;
	const Vector2f& getPosition() const;
	const int & getAttackPower() const;
	const int & getPoints() const;
	const int & getHp() const;
	
	//Game logic
	void move(RenderTarget& target, const float dirX, const float dirY);
	const bool canAttack();
	void addPoints(int points);

	//Update / render
	void update();
	void updateAttack();
	void render(RenderTarget& target);
};

