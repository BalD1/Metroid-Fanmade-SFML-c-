#include "Game.hpp"
#include "AudioManager.hpp"


/*
	Note pour ma conclusion :

	Alors d�j�, j'ai trouv� cet exercice vraiment cool dans
	le sens o� il m'a fais perdre les rep�res que j'avais avec
	l'inspecteur de unity, o� il suffisait de glisser-d�poser
	pour avoir une r�f�rence, et tout ce qu'il apporte en
	g�n�ral que le SFML n'a pas

	Du coup �a m'a forc� � r�fl�chir au-dessus de �a, ce qui
	est une bonne chose en soit mais en m�me temps j'ai fais des
	trucs sacr�ment d�gueulasses (comme l� par exemple, j'ai aucune
	id�e de pourquoi j'ai tout balanc� dans le Game comme un sagouin)

	Je suis juste un peu d��u de pas avoir p� bosser pendant les 
	vacances de No�l, mais c'est rest� amusant tr�s honn�tement

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