#include "Game.hpp"
#include "AudioManager.hpp"

int main()
{
	Game game;
	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}

}