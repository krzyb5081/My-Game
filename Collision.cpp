#include "Collision.h"

Collision::Collision() {
	load(new Player, new Obiekt, 0);
}

Collision::Collision(Player * player, Obiekt * gameItems, int iloscItems) {
	load(player, gameItems, iloscItems);
}

void Collision::load(Player * player, Obiekt * gameItems, int iloscItems) {
	this->player = player;
	this->gameItems = gameItems;
	this->iloscItems = iloscItems;
}

int Collision::checkPlayerCollision(Player player, Obiekt obiekt) {
	sf::FloatRect playerRect = player.sprite->getGlobalBounds();
	sf::FloatRect obiektRect = obiekt.sprite->getGlobalBounds();

	if (playerRect.intersects(obiektRect)) {
		return 1;
	}
	else {
		return 0;
	}
}

bool Collision::checkPlayerCollisionTop() {
	float playerPredkosc = *player->predkosc;


	player->move(0, -playerPredkosc);
	for (int i = 0; i < iloscItems; i++) {
		if ((*gameItems[i].isVisible == false) || (player->yPos - *gameItems[i].startY > *gameItems[i].height + 10)) {// llllllllllllalalalal sprawdzic to gunwo i lol i koniec bo nie dobre

		}
		else if (checkPlayerCollision(*player, gameItems[i]) == 1) {
			player->move(0, playerPredkosc);
			return false;
		}
	}
	player->move(0, playerPredkosc);
	return true;
}

bool Collision::checkPlayerCollisionBot() {
	float playerPredkosc = *player->predkosc;

	player->move(0, playerPredkosc);
	for (int i = 0; i < iloscItems; i++) {
		if ((*gameItems[i].isVisible == false) || (player->yPos - *gameItems[i].startY > *gameItems[i].height + 10)) {// llllllllllllalalalal sprawdzic to gunwo i lol i koniec bo nie dobre

		}
		else if (checkPlayerCollision(*player, gameItems[i]) == 1) {
			player->move(0, -playerPredkosc);
			return false;
		}
	}
	player->move(0, -playerPredkosc);
	return true;
}

bool Collision::checkPlayerCollisionLeft() {
	float playerPredkosc = *player->predkosc;

	player->move(-playerPredkosc, 0);
	for (int i = 0; i < iloscItems; i++) {
		if ((*gameItems[i].isVisible == false) || (player->yPos - *gameItems[i].startY > *gameItems[i].height + 10)) {// llllllllllllalalalal sprawdzic to gunwo i lol i koniec bo nie dobre

		}
		else if (checkPlayerCollision(*player, gameItems[i]) == 1) {
			player->move(playerPredkosc, 0);
			return false;
		}
	}
	player->move(playerPredkosc, 0);
	return true;
}

bool Collision::checkPlayerCollisionRight() {
	float playerPredkosc = *player->predkosc;

	player->move(playerPredkosc, 0);
	for (int i = 0; i < iloscItems; i++) {
		if ((*gameItems[i].isVisible == false) || (player->yPos - *gameItems[i].startY > *gameItems[i].height + 10)) {// llllllllllllalalalal sprawdzic to gunwo i lol i koniec bo nie dobre

		}
		else if (checkPlayerCollision(*player, gameItems[i]) == 1) {
			player->move(-playerPredkosc, 0);
			return false;
		}
	}
	player->move(-playerPredkosc, 0);
	return true;
}

void Collision::doCollision() {

	if (!checkPlayerCollisionTop()) {
		player->collisionTop = true;
	}
	else {
		player->collisionTop = false;
	}

	if (!checkPlayerCollisionBot()) {
		player->collisionBot = true;
	}
	else {
		player->collisionBot = false;
	}

	if (!checkPlayerCollisionLeft()) {
		player->collisionLeft = true;
	}
	else {
		player->collisionLeft = false;
	}

	if (!checkPlayerCollisionRight()) {
		player->collisionRight = true;
	}
	else {
		player->collisionRight = false;
	}
}



//ruch gracza nie wspolgra z kolizja zmienic zeby nie bylo kolizji z tym co sie chowa za plansza