#include "Game.hpp"
#include "AudioManager.hpp"


/*
	Note pour ma conclusion :

	Alors déjà, j'ai trouvé cet exercice vraiment cool dans
	le sens où il m'a fais perdre les repères que j'avais avec
	l'inspecteur de unity, où il suffisait de glisser-déposer
	pour avoir une référence, et tout ce qu'il apporte en
	général que le SFML n'a pas

	Du coup ça m'a forcé à réfléchir au-dessus de ça, ce qui
	est une bonne chose en soit mais en même temps j'ai fais des
	trucs sacrément dégueulasses (comme là par exemple, j'ai aucune
	idée de pourquoi j'ai tout balancé dans le Game comme un sagouin)

	Je suis juste un peu déçu de pas avoir pû bosser pendant les 
	vacances de Noël, mais c'est resté amusant très honnêtement

*/

int main()
{
	Game game;
	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}

}