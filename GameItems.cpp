#include "GameItems.h"
#include <iostream>

GameItems::GameItems(){
	initiate(new Player, 0);
}

GameItems::GameItems(Player * player, int iloscItems){
	initiate(player, iloscItems);
}

void GameItems::initiate(Player * player, int iloscItems){
	this->items = new std::vector<Obiekt>;
	this->player = player;
	this->iloscItems = new int(iloscItems);
}

void GameItems::ruszanie(){
	float playerX = this->player->worldPlayerCoordinatesX;
	float playerY = this->player->worldPlayerCoordinatesY;
	
	checkingVisibility();
	/*for (int i = 0; i < *this->iloscItems; i++) {

		if (*this->items->at(i).isVisible == true) {//ustawianie pozycji tylko sprajtom ktore sa widoczne

			if (*this->items->at(i).isFlat == true) {
				this->ruszaniePlaskichObiektow(i);
			}

			else {
				//pozycja obiektu wzgledem playera jest taka sama na ekranie dla sprajtow tylko ze sprajty maja pozycje nie na swiecie gry tylko na ekranie i dlatego potrzebne te obliczenia
				float spriteX = this->player->sprite->getPosition().x - (this->player->worldPlayerCoordinatesX - *this->items->at(i).startX);
				float spriteY = this->player->sprite->getPosition().y - (this->player->worldPlayerCoordinatesY - *this->items->at(i).startY);
				this->items->at(i).setSpritePosition(spriteX, spriteY);
			}
		}
	}
	checkingVisibility();*/
}

void GameItems::checkingVisibility(){
	
	const float pozycjaScenyY = 450;//pozycja y sprajta odpowiedzialnego za scene

	for (int i = 0; i < *this->iloscItems; i++){
		float odlegloscY = player->worldPlayerCoordinatesY - *this->items->at(i).startY;
		float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - pozycjaScenyY;
		
		//obiekt wychodzi albo zachodzi za scene ale juz albo jeszcze jest widoczny i nie jest plaski (plaskie obiekty nie moga byc za scena)
		if ( (*this->items->at(i).isFlat == false) && ((odlegloscY <= 2 * (*this->items->at(i).height) + odlegloscPlayeraOdKrawedzi) && (odlegloscY >= odlegloscPlayeraOdKrawedzi + *this->items->at(i).height)) ){
			*this->items->at(i).isVisible = true;
			*this->items->at(i).isBehindScene = true;
			this->items->at(i).sprite->setPosition(this->items->at(i).sprite->getPosition().x, pozycjaScenyY + odlegloscY - 2 * (*this->items->at(i).height) - odlegloscPlayeraOdKrawedzi);
		}

		//obiekt jest juz za scena, jest niewidoczny, obiekt jest za scena wiec obiekt isBehindScene = true
		else if (odlegloscY > 2 * (*this->items->at(i).height) + odlegloscPlayeraOdKrawedzi){
			*this->items->at(i).isVisible = false;
			*this->items->at(i).isBehindScene = true;
			
		}

		//dolna krawedz obiektu stoi juz/jeszcze na scenie ale nie wyszedl do konca i jest plaski
		else if ((*this->items->at(i).isFlat == true) && (odlegloscY > odlegloscPlayeraOdKrawedzi)) {
			*this->items->at(i).isVisible = true;
			*this->items->at(i).isBehindScene = true;
		}

		//dolna krawedz obiektu stoi juz/jeszcze na scenie
		else {
			*this->items->at(i).isVisible = true;
			*this->items->at(i).isBehindScene = false;
		}
	}
}

void GameItems::ruszaniePlaskichObiektow(int indexObiektu) {

	const float pozycjaScenyY = 450;//pozycja y sprajta odpowiedzialnego za scene

	float odlegloscY = player->worldPlayerCoordinatesY - *this->items->at(indexObiektu).startY;
	float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - pozycjaScenyY;


	sf::Vector2u obiectTextureSize = this->items->at(indexObiektu).sprite->getTexture()->getSize();
	sf::IntRect obiectRect = this->items->at(indexObiektu).sprite->getTextureRect();
	
	//wychodzi zza sceny
	if (*this->items->at(indexObiektu).isBehindScene == true) {

		

		float spriteX = this->player->sprite->getPosition().x - (this->player->worldPlayerCoordinatesX - *this->items->at(indexObiektu).startX);
		float spriteY = pozycjaScenyY;
		this->items->at(indexObiektu).setSpritePosition(spriteX, spriteY);


		//sprawdzenie czy wartosci nie sa za duze
		if (odlegloscY - odlegloscPlayeraOdKrawedzi <= obiectTextureSize.y) {
			obiectRect.top = odlegloscY - odlegloscPlayeraOdKrawedzi;
			
		}
		else {
			obiectRect.top = obiectTextureSize.y;
		}

		//sprawdzanie czy wartosci nie sa ujemne
		if (obiectTextureSize.y - obiectRect.top >= 0) {
			obiectRect.height = obiectTextureSize.y - obiectRect.top;
		}
		else {
			obiectRect.height = 0;
		}

		this->items->at(indexObiektu).sprite->setTextureRect(obiectRect);
	}

	else {
		
		obiectRect.left = 0;
		obiectRect.top = 0;
		obiectRect.width = obiectTextureSize.x;
		obiectRect.height = obiectTextureSize.y;
		this->items->at(indexObiektu).sprite->setTextureRect(obiectRect);

		float spriteX = this->player->sprite->getPosition().x - (this->player->worldPlayerCoordinatesX - *this->items->at(indexObiektu).startX);
		float spriteY = this->player->sprite->getPosition().y - (this->player->worldPlayerCoordinatesY - *this->items->at(indexObiektu).startY);
		this->items->at(indexObiektu).setSpritePosition(spriteX, spriteY);
	}
}