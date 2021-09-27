#include "HealthBar.h"

void HealthBar::initSprite(sf::Texture* texture, float pox_x, float pos_y)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pox_x, pos_y);
	this->sprite.scale(0.3f, 0.3f);
}

void HealthBar::initShape(float pox_x, float pos_y)
{
	this->shape.setSize(sf::Vector2f(this->hp, sprite.getGlobalBounds().height-20));
	this->shape.setPosition(pox_x+45, pos_y+10);
	this->shape.setFillColor(sf::Color::Green);
}

HealthBar::HealthBar(sf::Texture* texture, float pos_x, float pos_y, int hp)
{
	this->hp = hp;
	this->initSprite(texture,pos_x,pos_y);
	this->initShape(pos_x,pos_y);
}

HealthBar::~HealthBar()
{
}

void HealthBar::update()
{
	if (this->hp > 0) 
	{
		shape.setSize(sf::Vector2f(this->hp, sprite.getGlobalBounds().height - 20));
	}
}

void HealthBar::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(sprite);
}
