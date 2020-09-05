#ifndef MAPA_H
#define MAPA_H

#include "Obiekt.h"
#include "Player.h"
#include "Background.h"
#include "GameItems.h"

class Mapa {

    int wielkoscX;
    int wielkoscY;

	int iloscObiektow;

    Obiekt * obiekty;
	Player * player;
	Background * background;
	GameItems * gameItems;



public:
	
	Mapa();
	Mapa(Player * player, Background * background, GameItems * gameItems);

	void loadMap(Player * player, Background * background, GameItems * gameItems);
	void sortowanieObiektow();
	int getSizeX();
	int getSizeY();
	int getNumberOfObiects();
	Obiekt * getObiects();
	

};
#endif // MAPA_H
