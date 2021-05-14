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
	if ((player->moveTop) || (player->moveBot) || (player->moveLeft) || (player->moveRight)){

		checkingVisibility();

		float playerPredkosc = *player->predkosc;

		if (player->moveTop){
			for (int i = 0; i < iloscItems; i++){
				this->items[i].move(0, playerPredkosc);
			}
		}if (player->moveBot){
			for (int i = 0; i < iloscItems; i++){
				this->items[i].move(0, -playerPredkosc);
			}
		}if (player->moveLeft){
			for (int i = 0; i < iloscItems; i++){
				this->items[i].move(playerPredkosc, 0);
			}
		}if (player->moveRight){
			for (int i = 0; i < iloscItems; i++){
				this->items[i].move(-playerPredkosc, 0);
			}
		}
	}
}

void GameItems::checkingVisibility(){
	for (int i = 0; i < iloscItems; i++){
		float odlegloscY = player->yPos - *this->items[i].startY;
		float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - 350;//350 to pozycja y sprajta odpowiedzialnego za trawe                                                                                                                                               ZBUGOWANY BUG OMG

		if ((odlegloscY <= 2 * (*this->items[i].height) + odlegloscPlayeraOdKrawedzi) && (odlegloscY >= odlegloscPlayeraOdKrawedzi + *this->items[i].height)){//obiekt wychodzi albo zachodzi za scene ale juz albo jeszcze jest widoczny
			*this->items[i].isVisible = true;
			*this->items[i].isBehindScene = true;
			this->items[i].sprite->setPosition(this->items[i].sprite->getPosition().x, 350 + odlegloscY - 2 * (*this->items[i].height) - odlegloscPlayeraOdKrawedzi);
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