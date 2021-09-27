#pragma once
#include <SFML/Graphics.hpp>
class HealthBar
{
	sf::Sprite sprite;
	sf::RectangleShape shape;

	void initSprite(sf::Texture* texture, float pox_x, float pos_y);
	void initShape(float pox_x, float pos_y);


public:

	float hp;

	HealthBar(sf::Texture* texture, float pox_x, float pos_y, int hp);
	virtual ~HealthBar();

	void update();
	void render(sf::RenderTarget& target);
};

