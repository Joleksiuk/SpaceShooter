#include <iostream>
#include "Game.h"
#include <time.h>


int main()
{
	//Initialize Game engine
	Game game;
	srand((time(0)));

	while (game.running())
	{
		game.run();
	}

	return 0;
	
}