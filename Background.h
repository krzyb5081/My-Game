#pragma once

#include "Obiekt.h"
#include "Player.h"


class Background{
public:
	int * iloscObiektow;

	Obiekt * obiekty;
	Player * player;

	

	Background();
	Background(Player * player, int iloscObiektow);
	void initiate(Player * player, int iloscObiektow);
	void sterowanie();
};