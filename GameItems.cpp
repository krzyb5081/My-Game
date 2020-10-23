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
		float odleglosc = player->yPos - *items[i].startY;//odleglosc Y
		float odlegloscPlayeraOdKrawedzi = player->sprite->getPosition().y - 350;//350 to pozycja y sprajta odpowiedzialnego za trawe

		if ((odleglosc <= 2 * (*items[i].height) + odlegloscPlayeraOdKrawedzi) && (odleglosc >= odlegloscPlayeraOdKrawedzi + *items[i].height)){
			*items[i].isVisible = true;
			*items[i].warstwa = 1;
			items[i].sprite->setPosition(items[i].sprite->getPosition().x, 350 + odleglosc - 2 * (*items[i].height) - odlegloscPlayeraOdKrawedzi);
		}
		else if (odleglosc > 2 * (*items[i].height) + odlegloscPlayeraOdKrawedzi){
			*items[i].isVisible = false;
			*items[i].warstwa = 3;
			
		}
		else {
			*items[i].warstwa = 3;
		}
		
		//dodac sprawdzanko wszystkiego czy ma byc widzialne czy nie
	}
}

//przeniesc czekplejerkolizjontop i inne plejerkolizjony do Collision i w petli glownej uruchomic zaraz po sterowaniu bohaterem

//naprawic te krawedzie zeby tego juz nie bylo w backgroundach tez
