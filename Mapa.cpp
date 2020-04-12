#include "Mapa.h"

Mapa::Mapa(){
	loadMap(new Player, new Background, new GameItems);
}

Mapa::Mapa(Player * player, Background * background, GameItems * gameItems){
	loadMap(player, background, gameItems);
}

void Mapa::loadMap(Player * player, Background * background, GameItems * gameItems){
	wielkoscX = 1000;
	wielkoscY = 1000;

	this->player = player;
	
	iloscObiektow = 5;
	obiekty = new Obiekt[iloscObiektow];


	background->iloscObiektow = 3;
	background->obiekty = new Obiekt[3];

	// loading backgroundu //////////////////////////////////////////////////////////////////////////
	background->load(player, 3);

	obiekty[0].load("niebo.png", -400, 0, 0.004, 0);//niebo.png
	background->obiekty[0].copy(obiekty[0]);

	obiekty[1].load("drzewa.png", -400, 200 ,0.008, 0);//drzewa.png
	background->obiekty[1].copy(obiekty[1]);

	obiekty[2].load("trawa.bmp", -400, 350, 0, 0);//trawa.bmp
	background->obiekty[2].copy(obiekty[2]);
	
	//loading bohatera ///////////////////////////////////////////////////////////////////////////////
	obiekty[3].load("bohater.png", 600, 360, 0.2, 0);
	obiekty[3].setScale(0.15, 0.15);
	player->copy(obiekty[3]);

	//loading gameitemsow ////////////////////////////////////////////////////////////////////////
	gameItems->load(player, 1);

	obiekty[4].load("bohater.png", 400, 0, 0, 0);
	obiekty[4].setScale(0.15, 0.15);
	gameItems->items[0].copy(obiekty[4]);
	
	/*
	obiekty[5].load("bohater.png", 50, 500, 0, 0);
	obiekty[5].sprite->setScale(0.15, 0.15);
	gameItems->items[1].copy(obiekty[5]);*/

	//sprawdzanie widzialnosci gameItemsow ////////////////////////////////////////////////////////////
	//gameItems->checkingVisibility();

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
