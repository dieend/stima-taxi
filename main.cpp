#include "defines.hpp"
#include "GameEngine.hpp"
#include "TitleState.hpp"


int main ()
{
	// initialize the engine
	GameEngine game("Greedy Taxi");
	game.run(game.build<TitleState>(true));

	// main loop
	while( game.running() )
	{
		game.nextState();
		game.update();
		game.draw();
	}

	// leaving the scope of 'game' will cleanup the engine
    return 0;
}

