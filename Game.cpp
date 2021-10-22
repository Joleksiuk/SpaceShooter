#include "Game.h"
#include <iostream>

void Game::initBackground()
{
	this->background_1.setTexture(*this->textures["BACKGROUND"]);
	this->background_1.setScale(sf::Vector2f(this->resolutionModifier, this->resolutionModifier));
	this->background_2.setTexture(*this->textures["BACKGROUND"]);
	this->background_2.setScale(sf::Vector2f(this->resolutionModifier, this->resolutionModifier));
	

	background_1.setPosition(0.f, -background_1.getGlobalBounds().height + this->window->getSize().y);
	background_2.setPosition(0.f, -background_1.getGlobalBounds().height + this->window->getSize().y - background_2.getGlobalBounds().height);
	
}

void Game::initTextures()
{
	//Bullet texture
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullets/16.png");

	this->textures["HEALTHBAR"] = new Texture();
	this->textures["HEALTHBAR"]->loadFromFile("Textures/healthBar.png");

	this->textures["HEART"] = new Texture();
	this->textures["HEART"]->loadFromFile("Textures/heart.png");

	this->textures["BACKGROUND"] = new Texture();
	if (!this->textures["BACKGROUND"]->loadFromFile("Textures/space.png")) {
		std::cout << "ERROR:: COULD NOT find the texture :: Textures / space.png " << std::endl;
	};

	this->shipTextures.push_back (new Texture());
	this->shipTextures[0]->loadFromFile("Textures/ships/ship1.png");

	this->shipTextures.push_back(new Texture());
	this->shipTextures[1]->loadFromFile("Textures/ships/ship2.png");

	this->shipTextures.push_back(new Texture());
	this->shipTextures[2]->loadFromFile("Textures/ships/ship3.png");

	this->shipTextures.push_back(new Texture());
	this->shipTextures[3]->loadFromFile("Textures/ships/ship4.png");
	
}

void Game::initPlayer()
{
	this->player = new Player(this->resolutionModifier);
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initFontsAndTexts()
{
	//loading font
	if (!this->pointsFont.loadFromFile("Fonts/font.ttf")) {
		std::cout << "ERROR :: GAME :: INITGUI :: Cannot load font";
	}
	if (!this->gameOverFont.loadFromFile("Fonts/font.ttf")) {
		std::cout << "ERROR :: GAME :: INITGUI :: Cannot load font";
	}

	if (!this->pressRtoRestartFont.loadFromFile("Fonts/font.ttf")) {
		std::cout << "ERROR :: GAME :: INITGUI :: Cannot load font";
	}

	//init point text
	this->pointText.setFont(this->pointsFont);
	this->pointText.setCharacterSize(24);
	this->pointText.setPosition(550, 30);
	this->pointText.setFillColor(Color::White);
	this->pointText.setString("Points : ");

	//init gameOver text
	this->gameOverText.setFont(this->gameOverFont);
	this->gameOverText.setCharacterSize(40);
	this->gameOverText.setPosition(
		this->window->getSize().x/2.0,
		this->window->getSize().y/2.0);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setString("Game Over");

	//init press r to restart text
	this->pressRtoRestartText.setFont(this->gameOverFont);
	this->pressRtoRestartText.setCharacterSize(20);
	this->pressRtoRestartText.setPosition(
		this->window->getSize().x / 2.0,
		this->window->getSize().y / 2.0);
	this->pressRtoRestartText.setFillColor(Color::Red);
	this->pressRtoRestartText.setString("Press R to restart!");

}

void Game::updateTexts()
{
	if (this->gameOver)
	{
		this->gameOverText.setPosition(
			static_cast<double>((static_cast<double>(this->window->getSize().x) - static_cast<double>(this->gameOverText.getGlobalBounds().width ))) / 2.0,
			static_cast<double>((static_cast<double>(this->window->getSize().y) - static_cast<double>(this->gameOverText.getGlobalBounds().height))) / 2.0
		);

		this->pressRtoRestartText.setPosition(
			static_cast<double>((static_cast<double>(this->window->getSize().x) - static_cast<double>(this->pressRtoRestartText.getGlobalBounds().width))) / 2.0,
			static_cast<double>((static_cast<double>(this->window->getSize().y+80.0) - static_cast<double>(this->pressRtoRestartText.getGlobalBounds().height))) / 2.0
		);
	}
	else
	{
		this->pointText.setString("Points : " + std::to_string(this->player->getPoints()));
	}
}

void Game::initHealthBar()
{
	this->healthBar = new HealthBar(this->textures["HEART"], 20.f, 20.f, this->player->getHp());
}

void Game::initNewGame()
{
	this->clearTheOldGame();
	this->initPlayer();
	this->initHealthBar();
	this->initEnemies();
}

void Game::pauseTheGame()
{
	this->pausePhase = true;
}

void Game::unpauseTheGame()
{
	this->pausePhase = false;
}

Game::Game(RenderWindow* window)
{
	this->window = window;
	this->restartGame = false;
	this->gameOver = false;
	this->pausePhase = false;
	this->timeTicks = 0;
	this->resolutionModifier = sf::VideoMode::getDesktopMode().height / 800.f; //resolution modifier that you can multiply by to get right size of sprite relativly to screen resolution

	this->initFontsAndTexts();
	this->initTextures();
	this->initBackground();
	this->initPlayer();
	this->initHealthBar();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	//delete textures
	for(auto &i : this->textures)
	{
		delete i.second;
	}
	//delet bullets
	for (auto &i : this->bullets)
	{
		delete i;
	}

	for (auto *enemy : this->enemies) {
		delete enemy;
	}
}

void Game::run ()
{
	if (!this->pausePhase) {
		this->update();
		this->render();
	}
}

void Game::updateSpawnEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(this->window, shipTextures[rand() % 3], rand() % this->window->getSize().x, -100.f,this->resolutionModifier, 1, 1));
		this->spawnTimer = 0.f;
	}
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::gameIsPaused() const
{
	return this->pausePhase;
}

void Game::updateTimer()
{
	//timer adding to track timmings
	this->timeTicks += 1;
}

void Game::updateInput()
{
	//Move the player
	if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
		this->player->move(*this->window,-1.f, 0.f);
	else if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
		this->player->move(*this->window,1.f , 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
		this->player->move(*this->window,0.f, -1.f );
	else if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
		this->player->move(*this->window,0.f, 1.f );

	//Shooting
	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && this->player->canAttack() )
	{
		this->bullets.push_back( new Bullet(
				this->textures["BULLET"],
				this->player->getPosition().x+28 * this->resolutionModifier,
				this->player->getPosition().y-32 * this->resolutionModifier, 0.f, -1.f, 5.f * this->resolutionModifier));
	}
}

void Game::update()
{

	if (!gameOver) {

		this->updateBackground();
		//game timer update
		this->updateTimer();
		//move player
		this->updateInput();
		//update points
		this->updateTexts();
		//update player
		this->player->update();
		//update bullets
		this->updateBullets();
		//update Enemies
		this->updateSpawnEnemies();
		this->updateEnemiesAndCombat();
		//update Health Bar
		this->healthBar->update();
	}
	else {
		
		this->updateTexts();
		this->healthBar->update();

		//restarting the game
		if (Keyboard::isKeyPressed(Keyboard::Key::R))
		{
			this->restartGame = true;
		}

		if (this->restartGame == true)
		{
			this->gameOver = false;
			this->restartGame = false;
			this->initNewGame(); 
		}
	}
}

void Game::updateEnemiesAndCombat()
{
	//iterate through all current enemies on the screen
	for (int i = 0; i < this->enemies.size();++i) {
		this->enemies[i]->update();

		bool enemy_removed = false;
		//check collision with bullets
		for (int k = 0; k < this->bullets.size() && !enemy_removed; k++) 
		{
			if(this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
			
				//substract hp from enemy - depends on player attack Power
				this->enemies[i]->changeHp(this->player->getAttackPower());

				//Get attack recoil
				this->enemies[i]->moveAttackRecoil(this->bullets[k]->getRecoil());

				//erase the bullet
				this->bullets.erase(this->bullets.begin() + k);

				//if enemy's hp<=0 remove the enemy
				if (this->enemies[i]->getHp() <= 0) {
				
					this->player->addPoints(this->enemies[i]->getPoints());
					this->enemies.erase(this->enemies.begin() + i);
					enemy_removed = true;
					
				}
			}
		}
		// check collision with the player ship
		if (!enemy_removed)
		{
			if (this->player->getBounds().intersects(this->enemies[i]->getBounds())) {

				this->healthBar->subtractHp();
				std::cout << "PLAYER hit an enemy" << healthBar->getHp() << std::endl;
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}
	
		//check collision with window if enemy hasn't beeen removed
		if (!enemy_removed) 
		{
			//Remove enemies at the bottom of the screen
			if (this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
				std::cout << "ENEMY hit the screen" << healthBar->getHp() << std::endl;
				this->healthBar->subtractHp();
				this->enemies.erase(this->enemies.begin() + i);	
				enemy_removed = true;
			}
		}

		//check pattern and move enemy
		if (!enemy_removed)
		{
			switch (this->enemies[i]->getPattern())
			{
			case 0:
				break;
			case 1:
				if (this->enemies[i]->getMovementProgress() <= 50) {
					this->enemies[i]->changePosition(0, 3.f);
					
				}
				else
				{
					this->enemies[i]->changePosition(0, -3.f);
				}
				if(this->enemies[i]->getMovementProgress() == 100){
					this->enemies[i]->changeMovementProgress(-100);
				}
				else {
					this->enemies[i]->changeMovementProgress(1);
				}
				break;
			case 2:
				break;
			default:
				break;
			}

		}

		//check end game condition
		if (this->healthBar->getHp() <= 0)
		{
			this->gameOver = true;
		}
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets) 
	{
		bullet->update();
		//bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			-- counter;
		}
		++counter;
	}
}

void Game::updateBackground()
{
	this->background_1.move(0.f, 2.f);
	this->background_2.move(0.f, 2.f);

	if (background_1.getGlobalBounds().top >= this->window->getSize().y) {
		background_1.setPosition(0.f, -background_1.getGlobalBounds().height + this->window->getSize().y -background_2.getGlobalBounds().height);
	}
	if (background_2.getGlobalBounds().top >= this->window->getSize().y) {
		background_2.setPosition(0.f, -background_2.getGlobalBounds().height + this->window->getSize().y - background_1.getGlobalBounds().height);
	}

}

void Game::updatePauseInput()
{
	//Pausing the game
	if (Keyboard::isKeyPressed(Keyboard::Key::P))
	{
		this->pauseTheGame();
	}

	//Unpasuing the game
	if (Keyboard::isKeyPressed(Keyboard::Key::U))
	{
		this->unpauseTheGame();
	}
}

void Game::clearTheOldGame()
{
	this->bullets.clear();
	this->enemies.clear();
	delete player;
	delete healthBar;	
}

void Game::render()
{
	this->window->clear();

	this->renderBackground();

	this->player->render(*this->window);

	for (auto *bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies) {
		enemy->render(this->window);
	}
	this->healthBar->render(*this->window);

	this->renderGUI();

	this->window->display();

}

void Game::renderGUI()
{
	
	this->window->draw(this->pointText);
	if (this->gameOver)
	{
		this->window->draw(this->gameOverText);
		this->window->draw(this->pressRtoRestartText);
	}
}

void Game::renderBackground()
{
	this->window->draw(background_1); 
	this->window->draw(background_2);
}

void Game::renderDuringMenu()
{
	this->window->clear();

	this->renderBackground();

	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}
	this->healthBar->render(*this->window);

	this->renderGUI();
}
