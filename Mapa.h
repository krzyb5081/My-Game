#pragma once

#include "Obiekt.h"
#include "Collision.h"
#include "Player.h"
#include "Background.h"
#include "GameItems.h"

class Mapa {

    int wielkoscX;
    int wielkoscY;

	int iloscObiektow;
	int najwyzszaWarstwa;

    Obiekt * obiekty;
	Player * player;
	Collision * collision;
	Background * background;
	GameItems * gameItems;



public:
	
	Mapa();
	Mapa(Player * player, Collision * collision, Background * background, GameItems * gameItems);

	void loadMap(Player * player, Collision * collision, Background * background, GameItems * gameItems);
	void sortowanieObiektow();
	int getSizeX();
	int getSizeY();
	int getNumberOfObiects();
	Obiekt * getObiects();
	

};
