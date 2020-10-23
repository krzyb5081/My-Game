#pragma once

#include "Obiekt.h"
#include "Player.h"

class GameItems{

public:

	int iloscItems;
	Obiekt * items;
	Player * player;

	GameItems();
	GameItems(Player * player, int iloscItems);
	void load(Player * player, int iloscItems);
	void ruszanie();
	void checkingVisibility();

};