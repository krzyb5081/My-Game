#include "GameItems.h"

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
	if ((player->naKrawedziTop) || (player->naKrawedziDown) || (player->naKrawedziLeft) || (player->naKrawedziRight)){
		for (int i = 0; i < iloscItems; i++){
			if (player->naKrawedziTop){
				items[i].move(0, *player->predkosc);
			}if (player->naKrawedziDown){
				items[i].move(0, -*player->predkosc);
			}if (player->naKrawedziLeft){
				items[i].move(*player->predkosc, 0);
			}if (player->naKrawedziRight){
				items[i].move(-*player->predkosc, 0);
			}
		}
	}
}

void GameItems::checkingVisibility(){
	/*
	if (obiekty(kordy + wysokosc) < niz kordy planszy)
		to
		maja sie pojawic na wysokosci(kordy planszy + wysokosc obiektu)
		i
		isc w gore zamiast w dol
		i
		byc widoczne
		*/

	//dodac sprawdzanko wszystkiego czy ma byc widzialne czy nie
}