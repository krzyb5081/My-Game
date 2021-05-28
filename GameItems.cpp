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

			if (*this->items[i].isFlat == true) {
				this->ruszaniePlaskichObiektow(i);
			}

			else {
				//pozycja obiektu wzgledem playera jest taka sama na ekranie dla sprajtow tylko ze sprajty maja pozycje nie na swiecie gry tylko na ekranie i dlatego potrzebne te obliczenia
				float spriteX = this->player->sprite->getPosition().x - (this->player->worldPlayerCoordinatesX - *this->items[i].startX);
				float spriteY = this->player->sprite->getPosition().y - (this->player->worldPlayerCoordinatesY - *this->items[i].startY);
				this->items[i].setSpritePosition(spriteX, spriteY);
			}
		}
	}
	checkingVisibility();
}

void GameItems::checkingVisibility(){

	const float pozycjaScenyY = 450;//pozycja y sprajta odpowiedzialnego za scene

	for (int i = 0; i < iloscItems; i++){
		float odlegloscY = player->worldPlayerCoordinatesY - *this->items[i].startY;
		float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - pozycjaScenyY;

		//obiekt wychodzi albo zachodzi za scene ale juz albo jeszcze jest widoczny i nie jest plaski (plaskie obiekty nie moga byc za scena)
		if ( (*this->items[i].isFlat == false) && ((odlegloscY <= 2 * (*this->items[i].height) + odlegloscPlayeraOdKrawedzi) && (odlegloscY >= odlegloscPlayeraOdKrawedzi + *this->items[i].height)) ){
			*this->items[i].isVisible = true;
			*this->items[i].isBehindScene = true;
			this->items[i].sprite->setPosition(this->items[i].sprite->getPosition().x, pozycjaScenyY + odlegloscY - 2 * (*this->items[i].height) - odlegloscPlayeraOdKrawedzi);
		}

		//obiekt jest juz za scena, jest niewidoczny, obiekt jest za scena wiec obiekt isBehindScene = true
		else if (odlegloscY > 2 * (*this->items[i].height) + odlegloscPlayeraOdKrawedzi){
			*this->items[i].isVisible = false;
			*this->items[i].isBehindScene = true;
			
		}

		//dolna krawedz obiektu stoi juz/jeszcze na scenie ale nie wyszedl do konca i jest plaski
		else if ((*this->items[i].isFlat == true) && (odlegloscY > odlegloscPlayeraOdKrawedzi)) {
			*this->items[i].isVisible = true;
			*this->items[i].isBehindScene = true;
		}

		//dolna krawedz obiektu stoi juz/jeszcze na scenie
		else {
			*this->items[i].isVisible = true;
			*this->items[i].isBehindScene = false;
		}
	}
}

void GameItems::ruszaniePlaskichObiektow(int indexObiektu) {

	const float pozycjaScenyY = 450;//pozycja y sprajta odpowiedzialnego za scene

	float odlegloscY = player->worldPlayerCoordinatesY - *this->items[indexObiektu].startY;
	float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - pozycjaScenyY;


	sf::Vector2u obiectTextureSize = this->items[indexObiektu].sprite->getTexture()->getSize();
	sf::IntRect obiectRect = this->items[indexObiektu].sprite->getTextureRect();
	
	//wychodzi zza sceny
	if (*this->items[indexObiektu].isBehindScene == true) {

		

		float spriteX = this->player->sprite->getPosition().x - (this->player->worldPlayerCoordinatesX - *this->items[indexObiektu].startX);
		float spriteY = pozycjaScenyY;
		this->items[indexObiektu].setSpritePosition(spriteX, spriteY);

		//pozycjaScenyY + odlegloscY - 2 * (*this->items[indexObiektu].height) - odlegloscPlayeraOdKrawedzi

		obiectRect.left = 0;
		obiectRect.top = odlegloscY - odlegloscPlayeraOdKrawedzi;
		obiectRect.width = obiectTextureSize.x;
		obiectRect.height = obiectTextureSize.y - odlegloscY + odlegloscPlayeraOdKrawedzi;
		this->items[indexObiektu].sprite->setTextureRect(obiectRect);
	}

	else {
		
		obiectRect.left = 0;
		obiectRect.top = 0;
		obiectRect.width = obiectTextureSize.x;
		obiectRect.height = obiectTextureSize.y;
		this->items[indexObiektu].sprite->setTextureRect(obiectRect);

		float spriteX = this->player->sprite->getPosition().x - (this->player->worldPlayerCoordinatesX - *this->items[indexObiektu].startX);
		float spriteY = this->player->sprite->getPosition().y - (this->player->worldPlayerCoordinatesY - *this->items[indexObiektu].startY);
		this->items[indexObiektu].setSpritePosition(spriteX, spriteY);
	}
}