#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

//Pressing p - lanuching menu
// Pressing u - backing to game

class Menu
{
	//Window atributes
	RenderWindow* window;
	VideoMode videoMode;

	//Timers - program renerates 144 frames per second, pushing the button by user could last not one but many frames
	//so inctructions changed by pressing the button could be exectued many times.
	//For example pressing up button iterates to upper option - by pressing up button without timer it would be pressed (for example) 54 times so it would
	//iterate to up 54 times, it would be impossible to get the option you want. 

	float buttonPressingTimerMax;
	float buttonPressingTimer;

	//Graphics
	//the rectangle shape is the transparent black layer which is the background of menu
	RectangleShape background;

	//to achieve the fading effect every frame darkens the black transparent layer.
	//Theese variables track how many layers should be generated, and how many layers there currrently is
	float numberOfBlackLayersMax;
	float numberOfBlackLayers;

	//Font
	Font menuFont;

	//Texts
	//X and y cord of the text :: TODO Text should be centered automaticly
	float optionsFirstXCord;
	float optionsFirstYCord;

	//these variables help place automaticly all the option contained by the vector
	float optionsCurrentYPos;
	float spaceBetweenOptions;

	//Character size of the option text
	unsigned int optionsSize;
	
	//color of the options font
	sf::Color optionsColor;

	//All the text of the options are located in menuOption Vector
	std::vector<sf::Text*> menuOptions;

	//logic
	//Character size of the option text and number of the option ( index in vector)
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

