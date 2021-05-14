#include "Gra.h"

Gra::Gra() {
	this->obiekty = new Obiekt;

	player = new Player;
	collision = new Collision;
	background = new Background;
	gameItems = new GameItems;

	mapa.loadMap(player, collision, background, gameItems);
	this->obiekty = mapa.getObiects();
}

void Gra::loop(sf::RenderWindow & window){

	collision->doCollision();
	player->sterowanie();
	background->sterowanie();
	gameItems->ruszanie();
	rysuj(window);
	
}

void Gra::rysuj(sf::RenderWindow & window) {
	this->obiekty = mapa.sortowanieObiektow();

	for (int i = 0; i < mapa.getNumberOfObiects(); i++){
		if (*this->obiekty[i].isVisible == true){
			window.draw(*this->obiekty[i].sprite);
		}
	}

}


//zrobic sortowanie obiektow (do porzadku) w mapie zeby sie ukladaly od najnizszej warstwy do najwyzszej i moze dodac cos ze obiekt jest za plansza nie wiem xD