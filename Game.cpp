#include "Game.h"
#include <iostream>

void Game::initWindow()
{
	
	this->resolutionModifier = sf::VideoMode::getDesktopMode().height / 800.f; //resolution modifier that you can multiply by to get right size of sprite relativly to screen resolution
	this->videoMode.height = 800 * this->resolutionModifier -76;
	this->videoMode.width = 600 * this->resolutionModifier -76*3/4;
	this->window = new RenderWindow(this->videoMode,"Game 3", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	int center_x = (sf::VideoMode::getDesktopMode().width / 2) - (this->window->getSize().x / 2);
	int center_y = (sf::VideoMode::getDesktopMode().height / 2) - (this->window->getSize().y / 2)-36;
	this->window->setPosition( Vector2i(center_x,center_y));
	
}

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
	this->textures["BACKGROUND"]->loadFromFile("Textures/space.png");

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
	if (this->pointsFont.loadFromFile("Fonts/font.ttf")) {
		std::cout << "ERROR :: GAME :: INITGUI :: Cannot load font";
	}
	if (this->gameOverFont.loadFromFile("Fonts/font.ttf")) {
		std::cout << "ERROR :: GAME :: INITGUI :: Cannot load font";
	}
	//init game over text
	this->gameOverText.setFont(this->pointsFont);
	this->gameOverText.setCharacterSize(40);
	this->gameOverText.setPosition(300,300);
	this->gameOverText.setFillColor(Color::Red);

	//init point text
	this->pointText.setFont(this->pointsFont);
	this->pointText.setCharacterSize(24);
	this->pointText.setPosition(600, 30);
	this->pointText.setFillColor(Color::White);
	this->pointText.setString("Points : ");
}

void Game::initHealthBar()
{
	this->healthBar = new HealthBar(this->textures["HEART"], 20.f, 20.f, this->player->getHp());
}

Game::Game()
{
	this->gameOver = false;
	this->initWindow();
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
	this->update();
	this->render();
}

void Game::updateSpawnEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(this->window, shipTextures[rand() % 3], rand() % this->window->getSize().x - 20.f, -100.f,this->resolutionModifier));
		this->spawnTimer = 0.f;
	}
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::updatePollEvents()
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

	this->updateBackground();
	//Update Action listener

	this->updatePollEvents();

	//move player
	this->updateInput();

	//update points and health bar
	this->updateTexts();
	
	//update player
	this->player->update();

	//update Health Bar
	this->healthBar->update();

	//update bullets
	this->updateBullets();

	//update Enemies
	this->updateSpawnEnemies();
	this->updateEnemiesAndCombat();
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
		if (!enemy_removed) {
			if (this->player->getBounds().intersects(this->enemies[i]->getBounds())) {

				this->healthBar->subtractHp();
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
				enemy_removed = true;
				this->healthBar->subtractHp();
				this->enemies.erase(this->enemies.begin() + i);

				//TODO :: check end game condition
				//if () 
				//{
				//	this->gameOver = true;
				//}
			}
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

void Game::updateTexts()
{
	if (gameOver)
	{
		this->gameOverText.setString("GAME OVER");
	}
	else
	{
		this->pointText.setString("Points : " + std::to_string(this->player->getPoints()));
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
}

void Game::renderBackground()
{
	this->window->draw(background_1); 
	this->window->draw(background_2);
}
