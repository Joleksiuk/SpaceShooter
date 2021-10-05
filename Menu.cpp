#include "Menu.h"
#include <iostream>

void Menu::initBackground()
{
	this->background.setFillColor(sf::Color(0, 0, 0, 50));
	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->background.setPosition(0.f, 0.f);
}

void Menu::initFontsAndTexts()
{
	if (!this->menuFont.loadFromFile("Fonts/menuFont.ttf")) {
		std::cout << "ERROR :: GAME :: INITGUI :: Cannot load Menu Font";
	}

	this->optionsFirstXCord = 210.f;
	this->optionsFirstYCord = 320.f;
	this->optionsCurrentYPos = this->optionsFirstYCord;

	this->optionsSize = 30.f;
	this->chosenOptionSize = this->optionsSize + 10;
	this->spaceBetweenOptions = 60;
	this->optionsColor = sf::Color(255, 255, 255, 255);

	this->menuOptions.push_back(createOption(optionsCurrentYPos, "Aaaaaaaa"));
	this->menuOptions.push_back(createOption(optionsCurrentYPos, "Bbbbbbbb"));
	this->menuOptions.push_back(createOption(optionsCurrentYPos, "Cccccccc"));
	this->menuOptions.push_back(createOption(optionsCurrentYPos, "Dddddddd"));

}

Text* Menu::createOption(float pos_y, String text)
{
	Text* temporary = new Text();

	temporary->setFont(this->menuFont);
	temporary->setCharacterSize(this->optionsSize);
	temporary->setPosition(this->optionsFirstXCord, pos_y);
	temporary->setFillColor(this->optionsColor);
	temporary->setString(text);
	this->optionsCurrentYPos += temporary->getGlobalBounds().height+ this->spaceBetweenOptions;

	return temporary;
}

Menu::Menu(RenderWindow* window)
{
	this->numberOfBlackLayersMax = 100;
	this->numberOfBlackLayers = 0;

	this->chosenOption = 0;

	this->buttonPressingTimerMax = 10;
	this->buttonPressingTimer = this->buttonPressingTimerMax;

	this->window = window;
	this->initFontsAndTexts();
	this->initBackground();
}

Menu::~Menu()
{
	for (auto* text : menuOptions)
	{
		delete text;
	}
}

void Menu::run()
{
	this->update();
	this->render();
}

const bool Menu::running() const
{
	return this->window->isOpen();
}

void Menu::initPhase()
{
	this->numberOfBlackLayers = 0.0;
}

void Menu::update()
{
	this->updateBackground();
	this->updateUserInput();
	this->updateTexts();
}

void Menu::updateUserInput()
{
	
	this->buttonPressingTimer+=1.f;

	if (this->buttonPressingTimer >= this->buttonPressingTimerMax)
	{
		this->buttonPressingTimer = 0.f;

		//Moving on the menu
		if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
		{
			this->chosenOption++;
			if (this->chosenOption >= this->menuOptions.size())
			{
				this->chosenOption = 0;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
		{
			std::cout << this->chosenOption << std::endl;

			if (this->chosenOption == 0)
			{
				this->chosenOption = this->menuOptions.size() - 1;
			}
			else {
				this->chosenOption--;	
			}
		}
		//choosing an option
		if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
		{
			int test = -1;
			switch (this->chosenOption)
			{
			case 0:
				test = 0;
				break;
			case 1:
				test = 1;
				break;
			case 2:
				test = 2;
				break;
			case 3:
				test = 3;
				break;
			default:
				break;
			}
			std::cout << "Chosen option: " <<test<< std::endl;
		}
	}
}

void Menu::updateTexts()
{
	for (int i = 0; i < this->menuOptions.size(); i++)
	{
		if (chosenOption == i)
		{
			this->menuOptions[i]->setCharacterSize(this->chosenOptionSize);
		}
		else {
			this->menuOptions[i]->setCharacterSize(this->optionsSize);

		}	
	}
}

void Menu::updateBackground()
{

	if (this->numberOfBlackLayers <= this->numberOfBlackLayersMax)
	{
		this->background.setFillColor(sf::Color(0, 0, 0, numberOfBlackLayers));
		this->numberOfBlackLayers++;
	}
}

void Menu::render()
{
	this->renderBackground();

	this->renderGUI();

	this->window->display();
}

void Menu::renderGUI()
{
	for (auto *text: menuOptions)
	{
		this->window->draw(*text);
	}
}

void Menu::renderBackground()
{
	this->window->draw(background);	
}
