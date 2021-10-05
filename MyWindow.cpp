#include "MyWindow.h"

void MyWindow::initVariables()
{
	this->menuPhase = false;
	this->gamePhase = true;
}

void MyWindow::initWindow()
{
	this->resolutionModifier = sf::VideoMode::getDesktopMode().height / 800.f; //resolution modifier that you can multiply by to get right size of sprite relativly to screen resolution
	this->videoMode.height = 800 * this->resolutionModifier - 76;
	this->videoMode.width = 600 * this->resolutionModifier - 76 * 3 / 4;
	this->window = new RenderWindow(this->videoMode, "Game 3", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	int center_x = (sf::VideoMode::getDesktopMode().width / 2) - (this->window->getSize().x / 2);
	int center_y = (sf::VideoMode::getDesktopMode().height / 2) - (this->window->getSize().y / 2) - 36;
	this->window->setPosition(Vector2i(center_x, center_y));
}

MyWindow::MyWindow()
{
	this->initVariables();
	this->initWindow();
	this->game = new Game(this->window);
	this->menu = new Menu(this->window);
}

MyWindow::~MyWindow()
{
	delete game;
	delete menu;
}

void MyWindow::run()
{
	//updating poll events to be able to close the window
	this->updatePollEvents();

	//checking if the game was paused/unpaused
	this->game->updatePauseInput();

	this->updatePhases();

	
	if (menuPhase)
	{
		this->game->renderDuringMenu();
		this->menu->run();
	}

	if (gamePhase)
	{
		this->game->run();
	}

}

const bool MyWindow::running() const
{

	if (menuPhase)
	{
		return this->menu->running();
	}
	else if( gamePhase)
	{
		return this->game->running();
	}
	
}

void MyWindow::updatePhases()
{
	//initial entering menu ( the game is paused but menuPhase wasnt initialized yet)
	if (this->game->gameIsPaused() && this->gamePhase == true)
	{
		this->menu->initPhase();
	}

	if (this->game->gameIsPaused()) {
		this->menuPhase = true;
		this->gamePhase = false;
	}
	else {
		this->menuPhase = false;
		this->gamePhase = true;
	}
}

void MyWindow::updatePollEvents()
{
	Event event;
	while (this->window->pollEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			this->window->close();
			break;

		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
				this->window->close();
			break;

		}
	}
}

