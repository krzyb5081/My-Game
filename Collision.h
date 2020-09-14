#pragma once

#include "GameItems.h"

class Collision {

	int itemsAmount;
	Obiekt * gameItems;
	Player * player;
	
	Collision(Player * player, Obiekt * gameItems, int iloscItems);
	void load(Player * player, Obiekt * gameItems, int iloscItems);
	void checkCollisions();
};

