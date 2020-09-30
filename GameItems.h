#pragma once

#include "Obiekt.h"
#include "Player.h"
#include "Collision.h"

class GameItems{

	bool checkPlayerCollisionTop();
	bool checkPlayerCollisionBot();
	bool checkPlayerCollisionLeft();
	bool checkPlayerCollisionRight();

public:

	int iloscItems;
	Obiekt * items;
	Player * player;
	Collision * collision;

	GameItems();
	GameItems(Player * player, int iloscItems);
	void load(Player * player, int iloscItems);
	void ruszanie();
	void checkingVisibility();

};