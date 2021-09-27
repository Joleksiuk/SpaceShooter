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
	void initSprite();
	void initVariables();
	
public:
	Player();
	virtual ~Player();

	const Vector2f& getPosition() const;
	void move(RenderTarget& target, const float dirX, const float dirY );
	const bool canAttack();
	const int & getAttackPower() const;
	const int & getPoints() const;

	int getHp();
	void addPoints(int points);
	void update();
	void updateAttack();
	void render(RenderTarget& target);
};

