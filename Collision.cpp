#include "Collision.h"

Collision::Collision(Player * player, Obiekt * gameItems, int iloscItems) {
	load(player, gameItems, iloscItems);
}

void Collision::load(Player * player, Obiekt * gameItems, int iloscItems) {
	this->player = player;
	this->gameItems = gameItems;
	this->itemsAmount = iloscItems;
}

void Collision::checkCollisions() {

}