#include "Background.h"

Background::Background(){
	obiekty = new Obiekt;
	iloscObiektow = 0;
	player = new Player;
}

Background::Background(Player * player, int iloscObiektow){
	load(player, iloscObiektow);
}

void Background::load(Player * player, int iloscObiektow){
	obiekty = new Obiekt[iloscObiektow];

	this->player = player;
	this->iloscObiektow = iloscObiektow;
}

void Background::sterowanie() {
	sf::Keyboard keyboard;

	if (player->naKrawedziTop == true){
		if (keyboard.isKeyPressed(sf::Keyboard::Up)){
			obiekty[0].move(0, -*obiekty[0].predkosc);
			obiekty[1].move(0, -*obiekty[1].predkosc);
			//obiekty[2].move(0, obiekty[2].predkosc);
		}
	}
	if (player->naKrawedziDown == true){
		if (keyboard.isKeyPressed(sf::Keyboard::Down)) {
			obiekty[0].move(0, *obiekty[0].predkosc);
			obiekty[1].move(0, *obiekty[1].predkosc);
			//obiekty[2].move(0, -obiekty[2].predkosc);
		}
	}
	if (player->naKrawedziLeft == true){
		if (keyboard.isKeyPressed(sf::Keyboard::Left)) {
			obiekty[0].move(*obiekty[0].predkosc, 0);
			obiekty[1].move(*obiekty[1].predkosc, 0);
			obiekty[2].move(*obiekty[2].predkosc, 0);
		}
	}
	if (player->naKrawedziRight == true){
		if (keyboard.isKeyPressed(sf::Keyboard::Right)) {
			obiekty[0].move(-*obiekty[0].predkosc, 0);
			obiekty[1].move(-*obiekty[1].predkosc, 0);
			obiekty[2].move(-*obiekty[2].predkosc, 0);
		}
	}
}