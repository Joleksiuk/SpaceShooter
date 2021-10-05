#include <iostream>
#include <time.h>
#include "MyWindow.h"


int main()
{
	//Initialize Game engine
	MyWindow window;
	srand((time(0)));

	while (window.running())
	{
		window.run();
	}

	return 0;
	
}