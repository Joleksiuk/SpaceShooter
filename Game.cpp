#include "Game.h"

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode,"Game 3", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initBackground()
{
	this->background.setTexture(*this->textures["BACKGROUND"]);
	background.setPosition(0.f, -background.getGlobalBounds().height + this->window->getSize().y);
}

void Game::initTextures()
{
	//Bullet texture
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullets/16.png");

	this->textures["HEALTHBAR"] = new Texture();
	this->textures["HEALTHBAR"]->loadFromFile("Textures/healthBar.png");

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
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initGUI()
{
	//loading font
	if (this->pointsFont.loadFromFile("Fonts/font.ttf")) {
		std::cout << "ERROR :: GAME :: INITGUI :: Cannot load font";
	}
	if (this->gameOverFont.loadFromFile("Fonts/chunk.otf")) {
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
	this->healthBar = new HealthBar(this->textures["HEALTHBAR"], 10.0, 10.0, this->player->getHp());
}

Game::Game()
{
	this->gameOver = false;
	this->initWindow();
	this->initGUI();
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
		this->enemies.push_back(new Enemy(this->window, shipTextures[rand() % 3], rand() % this->window->getSize().x - 20.f, -100.f));
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
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		this->player->move(*this->window,-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		this->player->move(*this->window,1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
		this->player->move(*this->window,0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
		this->player->move(*this->window,0.f, 1.f);

	//Shooting
	if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack() )
	{
		this->bullets.push_back( new Bullet(
				this->textures["BULLET"],
				this->player->getPosition().x+28,
				this->player->getPosition().y-32, 0.f, -1.f, 5.f));
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
	this->updateGUI();
	
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
		//check collision with window
		if (!enemy_removed) 
		{
			//Remove enemies at the bottom of the screen
			if (this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
				enemy_removed = true;
				this->healthBar->hp -= enemies[i]->getDamage();
				this->enemies.erase(this->enemies.begin() + i);

				//if hp<=0 game ends;
				if (healthBar->hp <= 0) 
				{
					this->gameOver = true;
				}
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

void Game::updateGUI()
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
	this->background.move(0.f, 2.f);

	if (background.getGlobalBounds().top == 0) {
		background.setPosition(0.f, -background.getGlobalBounds().height + this->window->getSize().y);
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
	this->window->draw(background);
}
