#include "Background.h"

Background::Background(){
	this->initiate(new Player, 0, 0);
}

Background::Background(Player * player, int iloscObiektow, int sceneObiectIdNumber){
	this->initiate(player, iloscObiektow, sceneObiectIdNumber);
}

void Background::initiate(Player * player, int iloscObiektow, int sceneObiectIdNumber){
	obiekty = new Obiekt[iloscObiektow];

	this->player = player;
	this->iloscObiektow = iloscObiektow;
	this->sceneObiectIdNumber = sceneObiectIdNumber;

	this->sceneRectWidth = 400;
	this->sceneRectHeight = 100;

	

	//wyszukiwanie obiektu sceny
	int scenaIndex = 0;
	for (int i = 0; i < this->iloscObiektow; i++) {
		if (*obiekty[i].idNumber == this->sceneObiectIdNumber) {
			scenaIndex = i;
			break;
		}
	}

	obiekty[scenaIndex].sprite->setTextureRect(sf::IntRect())


}

void Background::sterowanie() {
	

	for (int i = 0; i < iloscObiektow; i++) {
		if (*this->obiekty[i].idNumber == this->sceneObiectIdNumber) {
			this->sterowanieScena(i);
		}

		if (player->moveTop == true) {
			obiekty[i].move(0, -*obiekty[i].predkosc);
		}
		if (player->moveBot == true) {
			obiekty[i].move(0, *obiekty[i].predkosc);
		}
		if (player->moveLeft == true) {
			obiekty[i].move(*obiekty[i].predkosc, 0);
		}
		if (player->moveRight == true) {
			obiekty[i].move(-*obiekty[i].predkosc, 0);
		}

	}
}

void Background::sterowanieScena(int scenaObiektIndex) {
	sf::IntRect sceneRect = this->obiekty[scenaObiektIndex].sprite->getTextureRect();

	if (player->moveTop == true) {
		obiekty[i].move(0, -*obiekty[i].predkosc);
	}
	if (player->moveBot == true) {
		obiekty[i].move(0, *obiekty[i].predkosc);
	}
	if (player->moveLeft == true) {
		obiekty[i].move(*obiekty[i].predkosc, 0);
	}
	if (player->moveRight == true) {
		obiekty[i].move(-*obiekty[i].predkosc, 0);
	}

	sf::IntRect newRect(sceneRectX, sceneRectY, );
	this->obiekty[scenaObiektIndex].sprite->setTextureRect();
}