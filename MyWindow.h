#pragma once
#include "Game.h"
#include "Menu.h"

//this class is managing all the "scenes"
//Main loop is concentrated around MyWindow Class
//Every "scene" such as menu or game is responsible only for their own compnents 

class MyWindow
{
	RenderWindow* window;
	VideoMode videoMode;

	bool gamePhase;
	bool menuPhase;
	Game* game;
	Menu* menu;

	//Resolution modifier
	float resolutionModifier;

	void initVariables();
	void initWindow();

public:
	MyWindow();
	virtual ~MyWindow();

	void run();
	const bool running() const;
	void updatePhases();
	void updatePollEvents();

};

