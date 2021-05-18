#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Dialog.h"
#include "Menu.h"
#include "Mapa.h"
#include "Obiekt.h"
#include "Background.h"
#include "GameItems.h"
#include "Collision.h"

class Gra {
private:
	
	int gameState;
	static const int GAME_STATE_GAME = 0;
	static const int GAME_STATE_MENU = 1;
	static const int GAME_STATE_DIALOG = 2;
	
	Menu menu;

	Dialog dialog;

	Mapa mapa;
	Obiekt * obiekty;

	Player * player;
	Collision * collision;
	Background * background;
	GameItems * gameItems;

	void loop(sf::RenderWindow & window);
	void gameStateControll(sf::RenderWindow & window);
	void rysuj(sf::RenderWindow & window);
	void doInteraction();

public:

    Gra();
	void main(sf::RenderWindow & window);
	

};
