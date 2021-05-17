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

	this->dialog.load("gudbaj_sztefi");//usunac to stad i dac gdzies w petli gry jak trzeba bedzie wywolac dialog
}

void Gra::main(sf::RenderWindow & window) {
	
	this->gameStateControll(window);
	
	switch (this->gameState) {
		case this->GAME_STATE_MENU:

			this->menu.rysuj(window);

			break;
		case this->GAME_STATE_GAME:

			this->loop(window);

			break;
		case this->GAME_STATE_DIALOG:
			
			this->dialog.main(window);

			break;
		default:
			break;
	}
}

void Gra::gameStateControll(sf::RenderWindow & window) {

	sf::Keyboard keyboard;

	switch (this->gameState) {
	case this->GAME_STATE_MENU:

		if (this->menu.zmienianieOpcji(window) == 0) {
			this->gameState = this->GAME_STATE_GAME;
		}

		break;
	case this->GAME_STATE_GAME:

		if (keyboard.isKeyPressed(sf::Keyboard::Escape)) {
			this->gameState = this->GAME_STATE_MENU;
		}
		
		this->collision->doInteraction();

		break;
	case this->GAME_STATE_DIALOG:

		if (this->dialog.dialogContinues == false) {
			this->gameState = this->GAME_STATE_GAME;
		}
		break;
	default:

		std::cout << "Gra nie wie w jakim jest stanie" << std::endl;
		window.close();
		break;
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