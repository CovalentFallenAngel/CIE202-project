#include "game.h"
#include<cstdlib>
#include "time.h"
int main()
{

	//Create an object of controller
	game Game;
	srand(time(0));
	Game.run();

	
	return 0;
}

