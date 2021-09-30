#include "HealthBar.h"

void HealthBar::initSprites(sf::Texture* texture)
{
	for (int i = 0; i < this->numberOfLivesMax; i++) {
		this->heartSprites.push_back(new sf::Sprite());
		this->heartSprites[i]->setTexture(*texture);
		this->heartSprites[i]->setPosition(this->xPosition, this->yPosition);
		this->heartSprites[i]->setScale(0.12f, 0.12f);

		this->xPosition += this->heartSprites[i]->getGlobalBounds().width + this->spaceBetween;
	}
}

void HealthBar::initVariables(int number_of_lives_max, float pos_x, float pos_y)
{
	this->xPosition = pos_x;
	this->yPosition = pos_y;
	this->spaceBetween = 10.f;
	this->numberOfLivesMax = number_of_lives_max;
	this->numberOfLives = this->numberOfLivesMax;
}

HealthBar::HealthBar(sf::Texture* texture, float pos_x, float pos_y, int number_of_lives_max)
{
	this->initVariables(number_of_lives_max, pos_x, pos_y);
	this->initSprites(texture);
}

HealthBar::~HealthBar()
{
	for (auto* heart : this->heartSprites) {
		delete heart;
	}
}

const float& HealthBar::getHp() const
{
	return this->numberOfLives;
}

void HealthBar::subtractHp()
{
	if (this->numberOfLives > 0) {
		this->numberOfLives -= 1;
	}
}

void HealthBar::update()
{
	int i = this->heartSprites.size()-1;
	while (this->heartSprites.size() != numberOfLives) {
		this->heartSprites.erase(heartSprites.begin() + i);
		i--;
	}
}

void HealthBar::render(sf::RenderTarget& target)
{
	for (auto* heart : this->heartSprites) {
		target.draw(*heart);
	}
}
