#pragma once

#include "Obiekt.h"
#include "Player.h"


class Background{

	int iloscObiektow;


public:
	Obiekt * obiekty;
	Player * player;

	

	Background();
	Background(Player * player, int iloscObiektow);
	void initiate(Player * player, int iloscObiektow);
	void sterowanie();
};