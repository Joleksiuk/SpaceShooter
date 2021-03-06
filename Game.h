#pragma once
#include <map>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "HealthBar.h"
#include <iostream>
#include <string> 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Game
{
private:

	//Window atributes
	RenderWindow* window;
	VideoMode videoMode;
	
	//managing the state of game
	bool gameOver;
	bool restartGame;
	bool pausePhase;
	unsigned int timeTicks;

	//Player;
	Player* player;

	//HealthBar
	HealthBar* healthBar;

	//Enemies;
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	//Bullets
	std::vector<Bullet*> bullets;

	//Fonts
	Font pointsFont;
	Font gameOverFont;
	Font pressRtoRestartFont;

	//Texts
	Text pointText;
	Text gameOverText;
	Text pressRtoRestartText;
	
	//Resources
	std::map<std::string,sf::Texture*> textures;
	std::vector<Texture*> shipTextures;

	//Graphics
	Sprite background_1;
	Sprite background_2;

	//Resolution modifier
	float resolutionModifier;

	//initializing functions
	void initBackground();
	void initTextures();
	void initPlayer();
	void initEnemies();
	void initFontsAndTexts();
	void initHealthBar();

	
public:
	//Constructor / Destructor
	Game(RenderWindow* window);
	virtual ~Game();

	//functions to restart the game
	void clearTheOldGame();
	void initNewGame();
	void pauseTheGame();
	void unpauseTheGame();

	void run();

	const bool running() const;
	const bool gameIsPaused() const;
	
	//******UPDATE*******
	void update();

	void updateTimer();
	void updateInput();
	void updateSpawnEnemies();
	void updateEnemiesAndCombat();
	void updateBullets();
	void updateTexts();
	void updateBackground();
	void updatePauseInput();


	//******RENDER*******
	void render();

	void renderGUI();
	void renderBackground();
	void renderDuringMenu();

};

