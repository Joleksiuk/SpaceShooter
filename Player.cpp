#include "Player.h"
#include <iostream>

void Player::initTexture()
{
	//load a texture from file
	if (!this->texture.loadFromFile("Textures/ship.png")) {
		std::cout << "ERROR::PLAYER::InitTexture - could not load texture ship.png";
	};
}

void Player::initSprite(float &resolutionModifier)
{
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale((0.15f* resolutionModifier), 0.15f * resolutionModifier);

}

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hp = 5;
	this->points = 0;
	this->attackPower = 2;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

Player::Player(float &resolutionModifier)
{
	this->movementSpeed = 3.f;
	this->initTexture();
	this->initSprite(resolutionModifier);
	this->initVariables();
}

Player::~Player()
{
}

const FloatRect& Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const Vector2f & Player::getPosition() const
{
	return this->sprite.getPosition();
}

void Player::move(RenderTarget& target, const float dirX, const float dirY)
{
	//moving sprite
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);

	//checking Window Bounds Collisions
	sf::FloatRect playerBounds = this->sprite.getGlobalBounds();
	//LEFT
	if (playerBounds.left <= 0.f) {
		this->sprite.setPosition(0.f, playerBounds.top);
	}

	playerBounds = this->sprite.getGlobalBounds();
	//RIGHT
	if (playerBounds.left + playerBounds.width >= target.getSize().x) {
		this->sprite.setPosition(target.getSize().x - playerBounds.width, playerBounds.top);
	}

	playerBounds = this->sprite.getGlobalBounds();
	//UP
	if (playerBounds.top <= 0.f) {
		this->sprite.setPosition(playerBounds.left, 0.f);
	}

	playerBounds = this->sprite.getGlobalBounds();
	//DOWN
	if (playerBounds.top + playerBounds.height >= target.getSize().y) {
		this->sprite.setPosition(playerBounds.left, target.getSize().y - playerBounds.height);
	}
}

//Checking if player can attack - adds cooldown between shots
const bool Player::canAttack()
{
	if (this->attackCooldown >= attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

const int & Player::getAttackPower() const
{
	return this->attackPower;
}

const int & Player::getPoints() const
{
	return this->points;
}

const int& Player::getHp() const
{
	return this->hp;
}

void Player::addPoints(int points)
{
	this->points += points;
}

void Player::update()
{
	this->updateAttack();
}

//updating cooldown attack
void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
	
}

//rendering player
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
