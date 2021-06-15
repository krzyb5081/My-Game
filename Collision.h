#pragma once

#include "Player.h"
#include "Obiekt.h"

#include <iostream>

class Collision {
	Player * player;
	std::vector<Obiekt> * gameItems;
	int * iloscItems;

	bool checkPlayerCollision(Player * player, Obiekt * obiekt);
public:

	Collision();
	Collision(Player * player, std::vector<Obiekt> * gameItems, int iloscItems);
	void load(Player * player, std::vector<Obiekt> * gameItems, int iloscItems);
	
	std::string doInteraction();

	void doCollision();
	bool checkPlayerCollisionTop();
	bool checkPlayerCollisionBot();
	bool checkPlayerCollisionLeft();
	bool checkPlayerCollisionRight();
};

