#pragma once

#include "Obiekt.h"
#include "Player.h"

class GameItems{

	void ruszaniePlaskichObiektow(int indexObiektu);

public:

	int * iloscItems;
	Obiekt * items;
	Player * player;

	GameItems();
	GameItems(Player * player, int iloscItems);
	void initiate(Player * player, int iloscItems);
	void ruszanie();
	void checkingVisibility();

};