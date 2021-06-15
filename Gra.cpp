#include "Gra.h"

Gra::Gra() {
	this->gameState = this->GAME_STATE_MENU;

	this->obiekty = new std::vector<Obiekt>;

	this->player = new Player;
	this->collision = new Collision;
	this->background = new Background;
	this->gameItems = new GameItems;

	mapa.loadMap("map.txt", player, collision, background, gameItems);
	this->obiekty = mapa.getObiects();

	this->dialog.load("gudbaj_sztefi");//usunac to stad i dac gdzies w petli gry jak trzeba bedzie wywolac dialog

	//usunac to
	this->gameState = this->GAME_STATE_MAP_EDITOR;
}

void Gra::loop(sf::RenderWindow & window){

	
	this->collision->doCollision();

	this->player->loop();
	this->background->sterowanie();
	this->gameItems->ruszanie();

	this->doInteraction();

	this->rysuj(window);
	
}

void Gra::loopMapEditor(sf::RenderWindow & window) {

	this->obiekty = mapa.getObiects();

	this->player->loop();
	this->background->sterowanie();
	this->gameItems->ruszanie();

	this->rysuj(window);
}

void Gra::doInteraction() {
	std::string interaction = this->collision->doInteraction();
	
	if (interaction.find("DIALOG ") != std::string::npos) {

		std::string dialogId;
		dialogId.assign(interaction, 7, interaction.length() - 7);//7 to dlugosc tekstu "DIALOG "

		this->gameState = this->GAME_STATE_DIALOG;
		this->dialog.load(dialogId);
		return;
		
	}
	else if (interaction == "") {
		//brak interakcji
	}
	else {
		std::cout << "unknown interaction type" << std::endl;
	}
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
	case this->GAME_STATE_MAP_EDITOR:

		this->loopMapEditor(window);

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

		break;
	case this->GAME_STATE_DIALOG:

		if (this->dialog.dialogContinues == false) {
			this->gameState = this->GAME_STATE_GAME;
		}
		break;
	case this->GAME_STATE_MAP_EDITOR:

		
		break;
	default:

		std::cout << "Gra nie wie w jakim jest stanie" << std::endl;
		window.close();
		break;
	}
}

void Gra::rysuj(sf::RenderWindow & window) {
	this->obiekty = mapa.sortowanieObiektow();

	for (int i = 0; i < mapa.getNumberOfObiects(); i++){
		if (*this->obiekty->at(i).isVisible == true){
			window.draw(*this->obiekty->at(i).sprite);
		}
	}

}


//zrobic sortowanie obiektow (do porzadku) w mapie zeby sie ukladaly od najnizszej warstwy do najwyzszej i moze dodac cos ze obiekt jest za plansza nie wiem xD