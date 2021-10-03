#include "Bullet.h"

Bullet::Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->bulletSprite.setTexture(*texture);
	this->bulletSprite.setPosition(pos_x, pos_y);
	this->bulletSprite.scale(0.2f * (sf::VideoMode::getDesktopMode().height / 1000.f),0.2f * (sf::VideoMode::getDesktopMode().height / 1000.f));
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->recoil = 20;
}

Bullet::~Bullet()
{
}

const FloatRect Bullet::getBounds() const
{
	return this->bulletSprite.getGlobalBounds();
}

const float Bullet::getRecoil() const
{
	return this->recoil;
}

void Bullet::update()
{
	//Movement
	this->bulletSprite.move(this->movementSpeed*this->direction);
}

void Bullet::render(RenderTarget * target)
{
	target->draw(this->bulletSprite);
}
