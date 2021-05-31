#include "Background.h"

Background::Background(){
	this->initiate(new Player, 0);
}

Background::Background(Player * player, int iloscObiektow){
	this->initiate(player, iloscObiektow);
}

void Background::initiate(Player * player, int iloscObiektow){
	obiekty = new Obiekt[iloscObiektow];

	this->player = player;
	this->iloscObiektow = new int(iloscObiektow);

}

void Background::sterowanie() {
	

	for (int i = 0; i < *this->iloscObiektow; i++) {
		if (*this->obiekty[i].isBehindScene == false) {//tylko background sceny ma ustawione na false
			continue;
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