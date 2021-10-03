#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class HealthBar
{
	//***************** ATRIBUTES *******************
	//Vector contains sprites of png hearts
	std::vector<sf::Sprite*> heartSprites;

	//Coordinates where healthbar will spawn
	float xPosition;
	float yPosition;
	float spaceBetween;

	//Variable of initial number of lives
	int numberOfLivesMax;
	//Variable of current number of lives
	int numberOfLives;

	//***************** FUNCTIONS *******************
	void initSprites(sf::Texture* texture);
	void initVariables(int number_of_lives_max, float pos_x, float pos_y);

public:

	//Constructor / Destructor
	HealthBar(sf::Texture* texture, float pox_x, float pos_y, int hp);
	virtual ~HealthBar();

	//Accessors
	const int& getHp()const;

	//Game logic
	void subtractHp();

	//Update / Render
	void update();
	void render(sf::RenderTarget& target);
};

