#pragma once

#include "Obiekt.h"
#include "Player.h"


class Background{

	int iloscObiektow;
	int sceneObiectIdNumber;

	int sceneRectWidth;
	int sceneRectHeight;

	void sterowanieScena(int scenaObiektIndex);

public:
	Obiekt * obiekty;
	Player * player;

	

	Background();
	Background(Player * player, int iloscObiektow, int sceneObiectIdNumber);
	void initiate(Player * player, int iloscObiektow, int sceneObiectIdNumber);
	void sterowanie();
};