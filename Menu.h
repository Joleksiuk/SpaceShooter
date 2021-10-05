#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Menu
{
	//Window atributes
	RenderWindow* window;
	VideoMode videoMode;

	//Timers
	float buttonPressingTimerMax;
	float buttonPressingTimer;

	//Graphics
	RectangleShape background;

	float numberOfBlackLayersMax;
	float numberOfBlackLayers;

	//Font
	Font menuFont;

	//Texts
	float optionsFirstXCord;
	float optionsFirstYCord;
	float optionsCurrentYPos;
	float spaceBetweenOptions;

	unsigned int optionsSize;
	
	sf::Color optionsColor;
	std::vector<sf::Text*> menuOptions;

	//logic
	unsigned int chosenOption;
	unsigned int chosenOptionSize;

	//Resolution modifier
	float resolutionModifier;

	//initializing functions
	void initBackground();
	void initFontsAndTexts();
	Text* createOption(float pos_y, String text);


public:

	Menu(RenderWindow* window);
	virtual ~Menu();

	void run();
	const bool running() const;
	void initPhase();

	//******UPDATE*******
	void update();

	void updateUserInput();
	void updateTexts();
	void updateBackground();


	//******RENDER*******
	void render();

	void renderGUI();
	void renderBackground();

};

