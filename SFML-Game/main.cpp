#include "Game.h"
#include <time.h>

int main() 
{
	srand((unsigned int)time(NULL));

	Game game;

	game.Running();

	//End of application
	return 0;
}