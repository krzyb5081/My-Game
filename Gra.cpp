#include "Gra.h"

Gra::Gra() {
	obiekty = new Obiekt;
	player = new Player;
	background = new Background;
	gameItems = new GameItems;

	mapa.loadMap(player, background, gameItems);
	obiekty = mapa.getObiects();
}

void Gra::loop(sf::RenderWindow & window){
	player->sterowanie();
	background->sterowanie();
	gameItems->ruszanie();
	rysuj(window);
	
}

void Gra::rysuj(sf::RenderWindow & window) {

	for (int i = 0; i < mapa.getNumberOfObiects(); i++){
		if (*obiekty[i].isVisible == true){
			window.draw(*obiekty[i].sprite);
		}
	}

}


//pozmieniac wszystkie pola w Obiekt na wskazniki!@!@!