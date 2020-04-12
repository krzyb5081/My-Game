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
	if ((player->naKrawedziTop) || (player->naKrawedziDown) || (player->naKrawedziLeft) || (player->naKrawedziRight)){

		

		for (int i = 0; i < iloscItems; i++){
			if (player->naKrawedziTop){


				////dziwne rzeczy alert!!!!!!!!!!!!!!!!!!!!!!!
				
				float odleglosc = 0;
				if (player->yPos > *items[i].startY){
					odleglosc = (player->yPos - *items[i].startY);
				} else if (player->yPos < *items[i].startY){
					odleglosc = (*items[i].startY - player->yPos);
				} else {
					odleglosc = 0;
				}
				
				std::cout << "Odleglosc: " << odleglosc << " height + 20: " << 2 * (*items[i].height) + 20 << std::endl;
				if ((odleglosc > 20) && (player->yPos - *items[i].startY > 0)){
					*items[i].isVisible = false;
				}
				else {
					*items[i].isVisible = true;
				}
				if ((player->yPos - *items[i].startY > 0) && (odleglosc <= 2 * (*items[i].height) + 20) && (odleglosc >= 20)){
					items[i].sprite->setPosition(items[i].sprite->getPosition().x, 350);
					std::cout << "if i hui";
				}
				else{
					items[i].move(0, *player->predkosc);
				}
				////dziwne rzeczy alert!!!!!!!!!!!!!!!!!!!!!!!

				//items[i].move(0, *player->predkosc);
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

/*
//if (500-300) <= 150
if ((plejer->xPos - obiekt.startX) <= obiekt->height + 50) && ((plejer->xPos - obiekt.startX) >= 50{
	//set pozycja na (x=stary x, y=500-50-(500-400) 
	obiekt->sprite->setPosition(obiekt->sprite->getPosition().x, plejer.xPos - 50 - (plajer->xPos - obiekt.startX));
}
*/


/*

*/