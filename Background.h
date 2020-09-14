#pragma once

#include "Obiekt.h"
#include "Player.h"


class Background{
public:
	Obiekt * obiekty;
	Player * player;
	int iloscObiektow;

	Background();
	Background(Player * player, int iloscObiektow);
	void load(Player * player, int iloscObiektow);
	void sterowanie();
};