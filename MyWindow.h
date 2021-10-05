#pragma once
#include "Game.h"
#include "Menu.h"

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

