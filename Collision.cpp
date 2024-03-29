#include "Collision.h"

Collision::Collision() {
	load(new Player, new std::vector<Obiekt>, 0);
}

Collision::Collision(Player * player, std::vector<Obiekt> * gameItems, int iloscItems) {
	load(player, gameItems, iloscItems);
}

void Collision::load(Player * player, std::vector<Obiekt> * gameItems, int iloscItems) {
	this->player = player;
	this->gameItems = gameItems;
	this->iloscItems = new int(iloscItems);
}

bool Collision::checkPlayerCollision(Player * player, Obiekt * obiekt) {
	sf::FloatRect playerRect = player->sprite->getGlobalBounds();
	sf::FloatRect obiektRect = obiekt->sprite->getGlobalBounds();

	float playerRectRight = playerRect.left + playerRect.width;
	float playerRectDown = playerRect.top + playerRect.height;

	float obiektRectRight = obiektRect.left + obiektRect.width;
	float obiektRectDown = obiektRect.top + obiektRect.height;


	//kolizyjna podstawa w ksztalcie polowki kwadratu (kwardrat uciety w polowie wysokosci) o dlugosci boku takiej jak szerokosc obiektu, chyba ze obiekt ma wieksza szerokosc niz wysokosc, wtedy kolizyjna podstawa ma ksztalt obiektu, czyli nie da sie za nim przejsc
	int wysokoscKolizyjnejPodstawyObiektu = 0;
	if (obiektRect.width/2 >= obiektRect.height) {
		wysokoscKolizyjnejPodstawyObiektu = obiektRect.height / 2;
	}
	else {
		wysokoscKolizyjnejPodstawyObiektu = obiektRect.width/2;
	}



	//sprajty musza sie dotknac (intersect) zeby robic te sprawdzenia bo inaczej sa bugi ze np koliduje z oddalonym obiektem bo zgadza sie wysokosc

	//jesli jest bezkolizyjnym (przenikalnym) obiektem
	if ( (*obiekt->colides == false) && (playerRect.intersects(obiektRect)) ) {
		obiekt->makeObiectTransparent(false);
		wysokoscKolizyjnejPodstawyObiektu = 0;//gracz jest przed obiektem jesli jego nogi sa nizej niz on

		//jesli player jest za obiektem (jesli dol playera jest wyzej niz gora kolizyjnej podstawy obiektu)
		if (obiektRectDown - wysokoscKolizyjnejPodstawyObiektu > playerRectDown) {

			playerRect.top -= obiektRect.height - wysokoscKolizyjnejPodstawyObiektu;
			*player->warstwa = *obiekt->warstwa - 1;

		}//jesli player jest przed obiektem (jesli dol playera jest nizej niz dol obiektu)
		else if (obiektRectDown < playerRectDown) {

			playerRect.top += playerRect.height - 10;// przesuniecie teoretycznego kwardaru w dol uwzgledniajac ze bohater ma stopy i chodzi nimi przed obiektem, czyli ma stopy ponizej poziomu dolu obiektu, -10 bo stopami nie chodzi po scianie tylko po podlodze przed obiektem
			*player->warstwa = *obiekt->warstwa;

		}
		return false;//nie koliduje na pewno bo jest bezkolizyjny

	}
	
	//jesli jest obiektem plaskim to ma byc zawsze pod nogami playera (plaski obiekt nie moze byc ustawiony jako bezkolizyjny)
	else if ((*obiekt->isFlat == true) && (playerRect.intersects(obiektRect))) {
		obiekt->makeObiectTransparent(false);

		*player->warstwa = *obiekt->warstwa;

		return false;//nie koliduje na pewno bo jest bezkolizyjny

	}

	
	else if (playerRect.intersects(obiektRect)) {

		obiekt->makeObiectTransparent(false);
		//jesli player jest w calosci za obiektem (jesli dol playera jest wyzej niz gora kolizyjnej podstawy obiektu, a gora playera jest nizej niz gora obiektu, player nie wychodzi tez z prawej ani z lewej strony obiektu, czyli jest w calosci za obiektem)
		if ((((obiektRect.contains(playerRect.left, playerRect.top)) && (obiektRect.contains(playerRectRight, playerRect.top))) && ((obiektRect.contains(playerRect.left, playerRectDown)) && (obiektRect.contains(playerRectRight, playerRectDown)))) && (obiektRectDown - wysokoscKolizyjnejPodstawyObiektu > playerRectDown)) {//czy kwadrat jest w kwadracie ale nadal uwzglednic kolizyjna podstawe!@!@
			
			playerRect.top -= obiektRect.height - wysokoscKolizyjnejPodstawyObiektu;
			*player->warstwa = *obiekt->warstwa - 1;
			obiekt->makeObiectTransparent(true);

		}//jesli player jest za obiektem (jesli dol playera jest wyzej niz gora kolizyjnej podstawy obiektu)
		else if (obiektRectDown - wysokoscKolizyjnejPodstawyObiektu > playerRectDown) {
			
			playerRect.top -= obiektRect.height - wysokoscKolizyjnejPodstawyObiektu;
			*player->warstwa = *obiekt->warstwa - 1;

		}//jesli player jest przed obiektem (jesli dol playera jest nizej niz dol obiektu)
		else if (obiektRectDown < playerRectDown) {
			
			playerRect.top += playerRect.height - 10;// przesuniecie teoretycznego kwardaru w dol uwzgledniajac ze bohater ma stopy i chodzi nimi przed obiektem, czyli ma stopy ponizej poziomu dolu obiektu, -10 bo stopami nie chodzi po scianie tylko po podlodze przed obiektem
			*player->warstwa = *obiekt->warstwa;

		}
		return playerRect.intersects(obiektRect);
	}
}

std::string Collision::doInteraction() {
	if((this->player->collisionTop)||(this->player->collisionBot)||(this->player->collisionLeft)||(this->player->collisionRight))//jesli player w ogole z czyms sie na prawde styka
	if (*this->player->use) {

		for (int i = 0; i < *this->iloscItems; i++) {
			if ((*gameItems->at(i).isVisible == false) || (*gameItems->at(i).isBehindScene == true)) {//jesli obiekt jest za scena albo jest niewidzialny to go nie sprawdzaj
				continue;
			}

			if (this->player->sprite->getGlobalBounds().intersects(this->gameItems->at(i).sprite->getGlobalBounds()) == true) {//interakcja z pierwszym napotkanym obiektem na podstawie prostej kolizji sprajtow
				if (*this->gameItems->at(i).interacts == true) {
					return "DIALOG "+ *this->gameItems->at(i).interactionData;
				}
			}
		}
	}

	return "";
}

void Collision::doCollision() {

	this->player->collisionTop = checkPlayerCollisionTop();
	this->player->collisionBot = checkPlayerCollisionBot();
	this->player->collisionLeft = checkPlayerCollisionLeft();
	this->player->collisionRight = checkPlayerCollisionRight();
}

bool Collision::checkPlayerCollisionTop() {
	float playerPredkosc = *player->predkosc;

	player->move(0, -playerPredkosc);//symulowanie ze player jest w miejscu kolizji
	for (int i = 0; i < *this->iloscItems; i++) {
		if ((*gameItems->at(i).isVisible == false) || ((*gameItems->at(i).isBehindScene == true)&&(*gameItems->at(i).isFlat == false)) ) {//jesli obiekt jest za scena i nie jest plaski albo jest niewidzialny to go nie sprawdzaj
			continue;
		}

		if (checkPlayerCollision(player, &gameItems->at(i)) == true) {//jesli zetknie sie z czymkolwiek
			player->move(0, playerPredkosc);
			return true;
		}
	}
	player->move(0, playerPredkosc);
	return false;
}

bool Collision::checkPlayerCollisionBot() {
	float playerPredkosc = *player->predkosc;

	player->move(0, playerPredkosc);//symulowanie ze player jest w miejscu kolizji
	for (int i = 0; i < *this->iloscItems; i++) {
		if ((*gameItems->at(i).isVisible == false) || ((*gameItems->at(i).isBehindScene == true) && (*gameItems->at(i).isFlat == false))) {//jesli obiekt jest za scena i nie jest plaski albo jest niewidzialny to go nie sprawdzaj
			continue;
		}

		if (checkPlayerCollision(player, &gameItems->at(i)) == true) {//jesli zetknie sie z czymkolwiek
			player->move(0, -playerPredkosc);
			return true;
		}
	}
	player->move(0, -playerPredkosc);
	return false;
}

bool Collision::checkPlayerCollisionLeft() {
	float playerPredkosc = *player->predkosc;

	player->move(-playerPredkosc, 0);//symulowanie ze player jest w miejscu kolizji
	for (int i = 0; i < *this->iloscItems; i++) {
		if ((*gameItems->at(i).isVisible == false) || ((*gameItems->at(i).isBehindScene == true) && (*gameItems->at(i).isFlat == false))) {//jesli obiekt jest za scena i nie jest plaski albo jest niewidzialny to go nie sprawdzaj
			continue;
		}

		if (checkPlayerCollision(player, &gameItems->at(i)) == true) {//jesli zetknie sie z czymkolwiek
			player->move(playerPredkosc, 0);
			return true;
		}
	}
	player->move(playerPredkosc, 0);
	return false;
}

bool Collision::checkPlayerCollisionRight() {
	float playerPredkosc = *player->predkosc;

	player->move(playerPredkosc, 0);//symulowanie ze player jest w miejscu kolizji
	for (int i = 0; i < *this->iloscItems; i++) {
		if ((*gameItems->at(i).isVisible == false) || ((*gameItems->at(i).isBehindScene == true) && (*gameItems->at(i).isFlat == false))) {//jesli obiekt jest za scena i nie jest plaski albo jest niewidzialny to go nie sprawdzaj
			continue;
		}

		if (checkPlayerCollision(player, &gameItems->at(i)) == true) {//jesli zetknie sie z czymkolwiek
			player->move(-playerPredkosc, 0);
			return true;
		}
	}
	player->move(-playerPredkosc, 0);
	return false;
}