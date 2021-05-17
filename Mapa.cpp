#include "Mapa.h"

#include <iostream>

Mapa::Mapa(){
	loadMap(new Player, new Collision, new Background, new GameItems);
}

Mapa::Mapa(Player * player, Collision * collision, Background * background, GameItems * gameItems){
	loadMap(player, collision, background, gameItems);
}

void Mapa::loadMap(Player * player, Collision * collision, Background * background, GameItems * gameItems){

	// ustawianie wlasciwosci mapy ////////////////////////////////////////////////////////////////////////
	wielkoscX = 1000;
	wielkoscY = 1000;
	this->najwyzszaWarstwa = 20;
	this->iloscObiektow = 16;

	this->obiekty = new Obiekt[iloscObiektow];

	// LOADING PLAYER /////////////////////////////////////////////////////////////////////////////////////
	this->obiekty[0].load(0, "Bohater.bmp", 650, 600, 1, 20, Obiekt::INTERACTION_TYPE_NONE, 0, false);
	this->obiekty[0].setScale(0.15, 0.15);

	
	player->copy(this->obiekty[0]);
	this->player = player;

	// LOADING BACKGROUND /////////////////////////////////////////////////////////////////////////////////
	this->obiekty[1].load(1, "Niebo.bmp", -400, 0, 0.004, 0, Obiekt::INTERACTION_TYPE_NONE, 0, true);//za scena
	this->obiekty[2].load(2, "Gory.bmp", -400, 200, 0.008, 1, Obiekt::INTERACTION_TYPE_NONE, 0, true);//za scena
	this->obiekty[3].load(3, "trawa.bmp", -400, 450, 0, 2, Obiekt::INTERACTION_TYPE_NONE, 0, false);//pierwsza zerowa warstwa 'przed scena' bo ten obiekt jest scena

	background->initiate(player, 3);
	background->obiekty[0].copy(this->obiekty[1]);
	background->obiekty[1].copy(this->obiekty[2]);
	background->obiekty[2].copy(this->obiekty[3]);
	
	// LOADING GAMEITEMS //////////////////////////////////////////////////////////////////////////////////
	this->obiekty[4].load(4, "bohater.bmp", -500, 0, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0, false);
	this->obiekty[5].load(5, "bohater1.bmp", -200, -100, 0, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337, false);
	this->obiekty[6].load(4, "bohater2.bmp", -200, -200, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0, false);
	this->obiekty[7].load(5, "bohater3.bmp", 40, 100, 0, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337, false);
	this->obiekty[8].load(4, "bohater4.bmp", 200, -30, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0, false);
	this->obiekty[9].load(5, "bohater5.bmp", 140, 100, 0, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337, false);
	this->obiekty[10].load(4, "budynek.bmp", -400, -1000, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0, false);
	this->obiekty[11].load(5, "budynek1.bmp", 40, -1400, 0, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337, false);
	this->obiekty[12].load(4, "budynek2.bmp", 400, -1800, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0, false);
	this->obiekty[13].load(5, "budynek3.bmp", 200, 20, -800, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337, false);
	this->obiekty[14].load(4, "budynek4.bmp", -400, -600, 0, 3, Obiekt::INTERACTION_TYPE_WALL, 0, false);
	this->obiekty[15].load(5, "budynek5.bmp", 800, -1000, 0, 3, Obiekt::INTERACTION_TYPE_USABLE, 1337, false);

	gameItems->initiate(player, 12);
	gameItems->items[0].copy(this->obiekty[4]);
	gameItems->items[1].copy(this->obiekty[5]);
	gameItems->items[2].copy(this->obiekty[6]);
	gameItems->items[3].copy(this->obiekty[7]);
	gameItems->items[4].copy(this->obiekty[8]);
	gameItems->items[5].copy(this->obiekty[9]);
	gameItems->items[6].copy(this->obiekty[10]);
	gameItems->items[7].copy(this->obiekty[11]);
	gameItems->items[8].copy(this->obiekty[12]);
	gameItems->items[9].copy(this->obiekty[13]);
	gameItems->items[10].copy(this->obiekty[14]);
	gameItems->items[11].copy(this->obiekty[15]);

	// LOADING GAMEITEMS TO COLLISION /////////////////////////////////////////////////////////////////////
	collision->load(player, gameItems->items, gameItems->iloscItems);

	//CHECKING GAMEITEMS VISIBILITY ///////////////////////////////////////////////////////////////////////
	gameItems->checkingVisibility();

}

Obiekt * Mapa::sortowanieObiektow(){
	
	Obiekt *posortowaneObiekty = new Obiekt[this->iloscObiektow];//najdalsza warstwa lezy za scena, czyli plansz¹ po której chodzi gracz, jezeli obiekt ma warstwê 12 ale ma ustawiony parametr isBehindScene na true to bêdzie pierwszy w sortowaniu przed warstw¹ 0. Dziêki temu ka¿dy obiekt zachowa swoj¹ warstwê nawet za scen¹, sprawi to ze obiekty stojace jeden na drugim beda wychodzic zza sceny w odpowiedniej kolejnosci
	int iloscPosortowanychObiektow = 0;//ilosc posortowanych obiektow
	

	int indexObiektuPlayeraWNieposortowanychObiektach = 0;
	for(int i = 0; i < this->iloscObiektow; i++) {//rozpoznawanie ktory obiekt jest obiektem playera
		if (this->player->isObiectAPlayer(this->obiekty[i])) {
			indexObiektuPlayeraWNieposortowanychObiektach = i;
			break;
		}
	}

	for (int warstwa = 0; warstwa <= this->najwyzszaWarstwa; warstwa++) {//sortowanie najpierw obiektow za scena (parametr isBehindScene = true)
		for (int i = 0; i < this->iloscObiektow; i++){
			if (*this->obiekty[i].isBehindScene == true) {
				if (*this->obiekty[i].warstwa == warstwa) {
					posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty[i]);
					iloscPosortowanychObiektow++;
				}
			}
		}
	}
	for (int warstwa = 0; warstwa <= this->najwyzszaWarstwa; warstwa++) {//sortowanie obiektow przed scena (parametr isBehindScene = false)
		for (int i = 0; i < this->iloscObiektow; i++) {
			if (i == indexObiektuPlayeraWNieposortowanychObiektach) {//jesli teraz leci warstwa playera i index playera to pomin go zeby wrzucic go do tej warstwy na koncu, to sprawi ze na pewno bedzie przed wszystkimi obiektami danej warstwy
				continue;
			}
			if (*this->obiekty[i].isBehindScene == false) {
				if (*this->obiekty[i].warstwa == warstwa) {
					posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty[i]);
					iloscPosortowanychObiektow++;
				}
			}
		}
		if (*this->obiekty[indexObiektuPlayeraWNieposortowanychObiektach].warstwa == warstwa) {
			posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty[indexObiektuPlayeraWNieposortowanychObiektach]);
			iloscPosortowanychObiektow++;
		}
	}

	
	for (int i = 0; i < iloscPosortowanychObiektow; i++) {
		this->obiekty[i].copy(posortowaneObiekty[i]);
	}
	delete[] posortowaneObiekty;
	
	return this->obiekty;
}

int Mapa::getSizeX(){
	return wielkoscX;
}

int Mapa::getSizeY(){
	return wielkoscY;
}

int Mapa::getNumberOfObiects(){
	return iloscObiektow;
}

Obiekt * Mapa::getObiects(){
	return this->obiekty;
}
