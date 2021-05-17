#pragma once

#include "Player.h"
#include "Obiekt.h"

class Collision {
	Player * player;
	Obiekt * gameItems;
	int iloscItems;

	bool checkPlayerCollision(Player * player, Obiekt * obiekt);
public:

	Collision();
	Collision(Player * player, Obiekt * gameItems, int iloscItems);
	void load(Player * player, Obiekt * gameItems, int iloscItems);
	
	std::string doInteraction();

	void doCollision();
	bool checkPlayerCollisionTop();
	bool checkPlayerCollisionBot();
	bool checkPlayerCollisionLeft();
	bool checkPlayerCollisionRight();
};

