#include "GameItems.h"
#include <iostream>

GameItems::GameItems(){
	load(new Player, 0);
}

GameItems::GameItems(Player * player, int iloscItems){
	load(player, iloscItems);
}

void GameItems::load(Player * player, int iloscItems){
	items = new Obiekt[iloscItems];
	this->player = player;
	this->iloscItems = iloscItems;
}

void GameItems::ruszanie(){
	if ((player->moveTop) || (player->moveBot) || (player->moveLeft) || (player->moveRight)){

		checkingVisibility();

		float playerPredkosc = *player->predkosc;

		if (player->moveTop){
			for (int i = 0; i < iloscItems; i++){
				items[i].move(0, playerPredkosc);
			}
		}if (player->moveBot){
			for (int i = 0; i < iloscItems; i++){
				items[i].move(0, -playerPredkosc);
			}
		}if (player->moveLeft){
			for (int i = 0; i < iloscItems; i++){
				items[i].move(playerPredkosc, 0);
			}
		}if (player->moveRight){
			for (int i = 0; i < iloscItems; i++){
				items[i].move(-playerPredkosc, 0);
			}
		}
	}
}

void GameItems::checkingVisibility(){
	for (int i = 0; i < iloscItems; i++){
		float odlegloscY = player->yPos - *items[i].startY;
		float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - 350;//350 to pozycja y sprajta odpowiedzialnego za trawe                                                                                                                                               ZBUGOWANY BUG OMG

		if ((odlegloscY <= 2 * (*items[i].height) + odlegloscPlayeraOdKrawedzi) && (odlegloscY >= odlegloscPlayeraOdKrawedzi + *items[i].height)){//obiekt wychodzi albo zachodzi za scene ale juz albo jeszcze jest widoczny
			*items[i].isVisible = true;
			*items[i].isBehindScene = true;
			items[i].sprite->setPosition(items[i].sprite->getPosition().x, 350 + odlegloscY - 2 * (*items[i].height) - odlegloscPlayeraOdKrawedzi);
		}
		else if (odlegloscY > 2 * (*items[i].height) + odlegloscPlayeraOdKrawedzi){//obiekt jest juz za scena, jest niewidoczny, obiekt jest za scena wiec obiekt isBehindScene = true
			*items[i].isVisible = false;
			*items[i].isBehindScene = true;
			
		}
		else {
			*items[i].isBehindScene = false;
		}
	}
}