#include "GameItems.h"
#include <iostream>

GameItems::GameItems(){
	initiate(new Player, 0);
}

GameItems::GameItems(Player * player, int iloscItems){
	initiate(player, iloscItems);
}

void GameItems::initiate(Player * player, int iloscItems){
	this->items = new Obiekt[iloscItems];
	this->player = player;
	this->iloscItems = iloscItems;
}

void GameItems::ruszanie(){
	float playerX = this->player->worldPlayerCoordinatesX;
	float playerY = this->player->worldPlayerCoordinatesY;

	checkingVisibility();
	for (int i = 0; i < iloscItems; i++) {
		if (*this->items[i].isVisible == true) {//ustawianie pozycji tylko sprajtom ktore sa widoczne

			//pozycja obiektu wzgledem playera jest taka sama na ekranie dla sprajtow tylko ze sprajty maja pozycje nie na swiecie gry tylko na ekranie i dlatego potrzebne te obliczenia
			float spriteX = this->player->sprite->getPosition().x - (this->player->worldPlayerCoordinatesX - *this->items[i].startX);
			float spriteY = this->player->sprite->getPosition().y - (this->player->worldPlayerCoordinatesY - *this->items[i].startY);
			this->items[i].setSpritePosition(spriteX, spriteY);
		}
	}
	checkingVisibility();
}

void GameItems::checkingVisibility(){

	const float pozycjaScenyY = 450;//pozycja y sprajta odpowiedzialnego za trawe

	for (int i = 0; i < iloscItems; i++){
		float odlegloscY = player->worldPlayerCoordinatesY - *this->items[i].startY;
		float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - pozycjaScenyY;

		if ((odlegloscY <= 2 * (*this->items[i].height) + odlegloscPlayeraOdKrawedzi) && (odlegloscY >= odlegloscPlayeraOdKrawedzi + *this->items[i].height)){//obiekt wychodzi albo zachodzi za scene ale juz albo jeszcze jest widoczny
			*this->items[i].isVisible = true;
			*this->items[i].isBehindScene = true;
			this->items[i].sprite->setPosition(this->items[i].sprite->getPosition().x, pozycjaScenyY + odlegloscY - 2 * (*this->items[i].height) - odlegloscPlayeraOdKrawedzi);
		}
		else if (odlegloscY > 2 * (*this->items[i].height) + odlegloscPlayeraOdKrawedzi){//obiekt jest juz za scena, jest niewidoczny, obiekt jest za scena wiec obiekt isBehindScene = true
			*this->items[i].isVisible = false;
			*this->items[i].isBehindScene = true;
			
		}
		else {
			*this->items[i].isBehindScene = false;
		}
	}
}