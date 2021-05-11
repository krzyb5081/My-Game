#include "Mapa.h"

#include <iostream>

Mapa::Mapa(){
	loadMap(new Player, new Collision, new Background, new GameItems);
}

Mapa::Mapa(Player * player, Collision * collision, Background * background, GameItems * gameItems){
	loadMap(player, collision, background, gameItems);
}

void Mapa::loadMap(Player * player, Collision * collision, Background * background, GameItems * gameItems){
	wielkoscX = 1000;
	wielkoscY = 1000;

	this->player = player;
	
	iloscObiektow = 6;
	obiekty = new Obiekt[iloscObiektow];


	background->iloscObiektow = 3;
	background->obiekty = new Obiekt[3];

	// loading backgroundu //////////////////////////////////////////////////////////////////////////
	background->load(player, 3);

	obiekty[0].load("Niebo.bmp", -400, 0, 0.004, 0);//niebo.png
	background->obiekty[0].copy(obiekty[0]);

	obiekty[1].load("Gory.bmp", -400, 200 ,0.008, 0);//drzewa.png
	background->obiekty[1].copy(obiekty[1]);

	obiekty[2].load("trawa.bmp", -400, 350, 0, 2);//trawa.bmp
	background->obiekty[2].copy(obiekty[2]);
	
	//loading bohatera ///////////////////////////////////////////////////////////////////////////////
	obiekty[3].load("Bohater.bmp", 650, 520, 0.2, 3);
	obiekty[3].setScale(0.15, 0.15);
	player->copy(obiekty[3]);

	//loading gameitemsow ////////////////////////////////////////////////////////////////////////
	gameItems->load(player, 2);

	obiekty[4].load("Cytadela.bmp", 350, 520, 0, 3);
	obiekty[4].setScale(4, 3);
	gameItems->items[0].copy(obiekty[4]);
	
	
	obiekty[5].load("bohater.png", 50, 500, 0, 3);
	obiekty[5].setScale(0.15, 0.15);
	gameItems->items[1].copy(obiekty[5]);

	//loading gameitemsow do collision //////////////////////////////////////////////////////////////
	
	collision->load(player, gameItems->items, gameItems->iloscItems);

	//sprawdzanie widzialnosci gameItemsow ////////////////////////////////////////////////////////////
	gameItems->checkingVisibility();

}

void Mapa::sortowanieObiektow(){
	Obiekt *miejsceNaObiekty = new Obiekt[iloscObiektow];

	int iloscObiektowWMiejscuNaObiekty = 0;
	int warstwa = 0;
	
	
	while (iloscObiektowWMiejscuNaObiekty < iloscObiektow){
		for (int i = 0; i < iloscObiektow; i++){
			if (*obiekty[i].warstwa == warstwa){
				miejsceNaObiekty[iloscObiektowWMiejscuNaObiekty].copy(obiekty[i]);
				iloscObiektowWMiejscuNaObiekty++;
			}
		}
		warstwa++;
	}

	for (int i = 0; i < iloscObiektow; i++) {
		obiekty[i].copy(miejsceNaObiekty[i]);
	}

	delete[] miejsceNaObiekty;
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
	return obiekty;
}
