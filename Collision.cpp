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

int Collision::checkPlayerCollision(Player * player, Obiekt * obiekt) {
	sf::FloatRect playerRect = player->sprite->getGlobalBounds();
	sf::FloatRect obiektRect = obiekt->sprite->getGlobalBounds();

	float playerRectRight = playerRect.left + playerRect.width;
	float playerRectDown = playerRect.top + playerRect.height;

	float obiektRectRight = obiektRect.left + obiektRect.width;
	float obiektRectDown = obiektRect.top + obiektRect.height;


	//kolizyjna podstawa w ksztalcie polowki kwadratu (kwardrat uciety w polowie wysokosci) o dlugosci boku takiej jak szerokosc obiektu, chyba ze obiekt ma wieksza szerokosc niz wysokosc, wtedy kolizyjna podstawa ma ksztalt obiektu, czyli nie da sie za nim przejsc
	int wysokoscKolizyjnejPodstawyObiektu = 0;
	if (obiektRect.width/2 >= obiektRect.height) {
		wysokoscKolizyjnejPodstawyObiektu = obiektRect.height;
	}
	else {
		wysokoscKolizyjnejPodstawyObiektu = obiektRect.width/2;
	}


	//jesli player jest w calosci za obiektem (jesli dol playera jest wyzej niz gora kolizyjnej podstawy obiektu, a gora playera jest nizej niz gora obiektu, player nie wychodzi tez z prawej ani z lewej strony obiektu, czyli jest w calosci za obiektem)
	if ((((obiektRect.contains(playerRect.left, playerRect.top)) && (obiektRect.contains(playerRectRight, playerRect.top))) && ((obiektRect.contains(playerRect.left, playerRectDown)) && (obiektRect.contains(playerRectRight, playerRectDown)))) && (obiektRectDown - wysokoscKolizyjnejPodstawyObiektu > playerRectDown)) {//czy kwadrat jest w kwadracie ale nadal uwzglednic kolizyjna podstawe!@!@
		
	}//jesli player jest za obiektem (jesli dol playera jest wyzej niz gora kolizyjnej podstawy obiektu)
	else if (obiektRectDown - wysokoscKolizyjnejPodstawyObiektu > playerRectDown) {
		playerRect.top -= obiektRect.height - wysokoscKolizyjnejPodstawyObiektu;

	}//jesli player jest przed obiektem (jesli dol playera jest nizej niz dol obiektu)
	else if (obiektRectDown < playerRectDown) {
		playerRect.top += playerRect.height - 10;// przesuniecie teoretycznego kwardaru w dol uwzgledniajac ze bohater ma stopy i chodzi nimi przed obiektem, czyli ma stopy ponizej poziomu dolu obiektu, -10 bo stopami nie chodzi po scianie tylko po podlodze przed obiektem
	
	}


	int intersects = 0;
	if (playerRect.intersects(obiektRect)) {
		intersects = 1;
	}
	else {
		intersects = 0;
	}

	return intersects;
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

bool Collision::checkPlayerCollisionTop() {
	float playerPredkosc = *player->predkosc;


	player->move(0, -playerPredkosc);
	for (int i = 0; i < iloscItems; i++) {
		if ((*gameItems[i].isVisible == false) || (player->worldPlayerCoordinatesY - *gameItems[i].startY > *gameItems[i].height + 10)) {// sprawdzanie czy nie zaszla bledna kolizja z obiektem wychodzacym zza planszy albo wchodzacym za nia (watpliwej jakosci)

		}
		else if (checkPlayerCollision(player, &gameItems[i]) == 1) {
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
		if ((*gameItems[i].isVisible == false) || (player->worldPlayerCoordinatesY - *gameItems[i].startY > *gameItems[i].height + 10)) {// sprawdzanie czy nie zaszla bledna kolizja z obiektem wychodzacym zza planszy albo wchodzacym za nia (watpliwej jakosci)
		}
		else if (checkPlayerCollision(player, &gameItems[i]) == 1) {
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
		if ((*gameItems[i].isVisible == false) || (player->worldPlayerCoordinatesY - *gameItems[i].startY > *gameItems[i].height + 10)) {// sprawdzanie czy nie zaszla bledna kolizja z obiektem wychodzacym zza planszy albo wchodzacym za nia (watpliwej jakosci)

		}
		else if (checkPlayerCollision(player, &gameItems[i]) == 1) {
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
		if ((*gameItems[i].isVisible == false) || (player->worldPlayerCoordinatesY - *gameItems[i].startY > *gameItems[i].height + 10)) {// sprawdzanie czy nie zaszla bledna kolizja z obiektem wychodzacym zza planszy albo wchodzacym za nia (watpliwej jakosci)

		}
		else if (checkPlayerCollision(player, &gameItems[i]) == 1) {
			player->move(-playerPredkosc, 0);
			return false;
		}
	}
	player->move(-playerPredkosc, 0);
	return true;
}

//ruch gracza nie wspolgra z kolizja zmienic zeby nie bylo kolizji z tym co sie chowa za plansza