#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "Obiekt.h"
#include "Background.h"
#include "GameItems.h"

class Gra {

	Mapa mapa;
	Obiekt * obiekty;
	Player * player;
	Background * background;
	GameItems * gameItems;

public:

    Gra();
	void loop(sf::RenderWindow & window);
	void rysuj(sf::RenderWindow & window);

};
