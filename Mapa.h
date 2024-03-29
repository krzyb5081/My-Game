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

    std::vector<Obiekt> * obiekty;
	Player * player;
	Collision * collision;
	Background * background;
	GameItems * gameItems;



public:
	
	Mapa();
	Mapa(std::string mapFile, Player * player, Collision * collision, Background * background, GameItems * gameItems);

	void loadMap(std::string mapFile, Player * player, Collision * collision, Background * background, GameItems * gameItems);
	void saveMap(std::string mapFile);

	void loadObiectFromFile(std::string obiectFile);

	std::vector<Obiekt> * sortowanieObiektow();
	int getSizeX();
	int getSizeY();
	int getNumberOfObiects();
	std::vector<Obiekt> * getObiects();
	

};
