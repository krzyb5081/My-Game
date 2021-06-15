#pragma once

#include "Obiekt.h"
#include "Player.h"

class GameItems{

	void ruszaniePlaskichObiektow(int indexObiektu);

public:

	std::vector<Obiekt> * items;
	int * iloscItems;
	Player * player;

	GameItems();
	GameItems(Player * player, int iloscItems);
	void initiate(Player * player, int iloscItems);
	void ruszanie();
	void checkingVisibility();

};