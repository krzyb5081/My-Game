#include "Gra.h"

Gra::Gra() {
	this->gameState = this->GAME_STATE_DIALOG;

	this->obiekty = new Obiekt;

	player = new Player;
	collision = new Collision;
	background = new Background;
	gameItems = new GameItems;

	mapa.loadMap(player, collision, background, gameItems);
	this->obiekty = mapa.getObiects();
}

void Gra::main(sf::RenderWindow & window) {
	
	sf::Keyboard keyboard;

	if (keyboard.isKeyPressed(sf::Keyboard::Escape)) {
		this->gameState = this->GAME_STATE_MENU;
	}
	
	switch (this->gameState) {
		case this->GAME_STATE_MENU:

			if (this->menu.zmienianieOpcji(window) == 0) {
				this->gameState = this->GAME_STATE_GAME;
			}
			this->menu.rysuj(window);

		break;
		case this->GAME_STATE_GAME:

			loop(window);

		break;
		case this->GAME_STATE_DIALOG:

			this->dialog.setDialog("halu_sztefi");
		break;
		default:

		std::cout << "Gra nie wie w jakim jest stanie" << std::endl;
		window.close();
	}
}

void Gra::loop(sf::RenderWindow & window){

	

	collision->doCollision();
	player->loop();
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