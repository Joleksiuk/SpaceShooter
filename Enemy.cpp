#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);
	this->shape.setFillColor(Color(rand() % 255+1, rand() % 255 + 1, rand() % 255+1, 255));
}

void Enemy::initVariables()
{
	this->type			= std::stof(std::to_string(rand() % 4) + "." + std::to_string(rand() % 10));
	this->points		= rand() % 8 + 3; 
	this->speed			= static_cast<float>(this->points / 3);
	this->hpMax			= static_cast<int>(this->points);
	this->hp			= this->hpMax;
	this->damage		= this->points;
}

void Enemy::initSprite(RenderTarget * target, Texture * texture, float pos_x, float pos_y)
{
	this->sprite.setTexture(*texture);

	this->sprite.setScale(this->type, this->type);

	if (pos_x + this->sprite.getGlobalBounds().width >= target->getSize().x) {
		pos_x = pos_x - this->sprite.getGlobalBounds().width;
	}

	this->sprite.setPosition(pos_x, pos_y);

}

Enemy::Enemy(RenderTarget * target, Texture* texture, float pos_x, float pos_y)
{	
	this->initVariables();
	this->initSprite(target, texture, pos_x, pos_y);

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

void Enemy::changeHp(int change)
{
	this->hp -= change;
}

void Enemy::moveAttackRecoil(const float& recoil)
{
	this->sprite.move(0.f, -recoil);
}


const FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Enemy::update()
{
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(RenderTarget * target)
{
	target->draw(this->sprite);
}
