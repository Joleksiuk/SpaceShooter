#include "Enemy.h"
#include <iostream>

void Enemy::initVariables()
{
	this->points		= rand() % 8 + 3; 
	this->speed			= static_cast<float>(this->points / 3);
	this->hpMax			= static_cast<int>(this->points);
	this->hp			= this->hpMax;
	this->damage		= this->points;
}

void Enemy::initSprite(RenderTarget * target, Texture * texture, float pos_x, float pos_y, float &resolutionModifier, int type, int pattern)
{
	//adding texture to enemy 
		this->sprite.setTexture(*texture);
	//adding diffrent paramets depending on enemy type
	switch (type)
	{
	case 0:
		this->sprite.setScale(1 * resolutionModifier, 1 * resolutionModifier);
		break;
	case 1:
		this->sprite.setScale(1 * resolutionModifier, 1 * resolutionModifier);
		this->shoot_cooldown = 100;
		break;
	case 2:
		this->sprite.setScale(2 * resolutionModifier, 2 * resolutionModifier);
		this->shoot_cooldown = 55;
		break;
	default:
		break;
	}
	 //setting up move_pat depending on given pattern
	switch (pattern)
	{
	case 0:
		this->move_pat = 0;
		break;
	case 1:	
		//pattern 1 will be a moving right/left for 50 pixels pattern test
		this->move_pat = 1;
		break;
	case 2:
		this->move_pat = 2;
		break;
	default:
		break;
	}

	//initializing move_prog
	this->move_prog = 0;

	//improving position of the sprite if it spawned not entilery in the screen
	if (pos_x + this->sprite.getGlobalBounds().width >= target->getSize().x) {
		pos_x = pos_x - this->sprite.getGlobalBounds().width;
	}

	this->sprite.setPosition(pos_x, pos_y);

}

Enemy::Enemy(RenderTarget * target, Texture* texture, float pos_x, float pos_y, float &resolutionModifier,int type, int pattern)
{	
	this->initVariables();
	this->initSprite(target, texture, pos_x, pos_y, resolutionModifier, type, pattern);

}

Enemy::~Enemy()
{
}

const int & Enemy::getPoints() const
{
	return this->points;
}

const int & Enemy::getDamage() const
{
	return this->damage;
}

const int & Enemy::getHp() const
{
	return this->hp;
}

void Enemy::changePosition(int direction, float change)
{
	switch (direction)
	{
	case 0:
		//left or right
		this->sprite.move(change, 0.f);
		break;
	case 1:
		//up or down
		this->sprite.move(0.f, change);
		break;
	default:
		break;
	}
	
}

void Enemy::changeMovementProgress(int change)
{
	this->move_prog += change;
}

void Enemy::changeHp(int change)
{
	this->hp -= change;
}

void Enemy::changeShootCooldown(int change)
{
	this->shoot_cooldown = change;
}

void Enemy::moveAttackRecoil(const float& recoil)
{
	this->sprite.move(0.f, -recoil);
}


const FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getPattern() const
{
	return this->move_pat;
}

const int& Enemy::getMovementProgress() const
{
	return this->move_prog;
}

const int& Enemy::getShootCooldown() const
{
	return this->shoot_cooldown;
}

const Vector2f& Enemy::getPosition() const
{
	return this->sprite.getPosition();
}

void Enemy::update()
{
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(RenderTarget * target)
{
	target->draw(this->sprite);
}
