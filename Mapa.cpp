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
	this->iloscObiektow = 38;

	this->obiekty = new Obiekt[iloscObiektow];

	// LOADING PLAYER /////////////////////////////////////////////////////////////////////////////////////
	this->obiekty[0].load(0, "bohater.bmp", 650, 600, 1, 20, true, false, "", false);
	this->obiekty[0].setScale(0.15, 0.15);

	
	player->copy(this->obiekty[0]);
	this->player = player;

	// LOADING BACKGROUND /////////////////////////////////////////////////////////////////////////////////
	this->obiekty[1].load(1, "niebo.bmp", -400, 0, 0.01, 0, false, false, "", true);//za scena
	this->obiekty[2].load(2, "slonce.bmp", 210, -210, 0, 1, false, false, "", true);//za scena
	this->obiekty[3].load(3, "gory.bmp", -400, 200, 0.02, 2, false, false, "", true);//za scena
	this->obiekty[4].load(4, "trawa.bmp", -400, 450, 0, 0, false, false, "", false);//pierwsza zerowa warstwa 'przed scena' bo ten obiekt jest scena

	background->initiate(player, 4);
	background->obiekty[0].copy(this->obiekty[1]);
	background->obiekty[1].copy(this->obiekty[2]);
	background->obiekty[2].copy(this->obiekty[3]);
	background->obiekty[3].copy(this->obiekty[4]);
	
	// LOADING GAMEITEMS //////////////////////////////////////////////////////////////////////////////////
	this->obiekty[5].load(5, "bohater.bmp", -500, 0, 0, 3, true, true, "jotpe", false);
	this->obiekty[6].load(6, "bohater1.bmp", -200, -100, 0, 3, true, true, "jotpe", false);
	this->obiekty[7].load(7, "bohater2.bmp", -200, -200, 0, 3, true, true, "halu_sztefi", false);
	this->obiekty[8].load(8, "bohater3.bmp", 40, 100, 0, 3, true, true, "halu_sztefi", false);
	this->obiekty[9].load(9, "bohater4.bmp", 200, -30, 0, 3, true, true, "gudbaj_sztefi", false);
	this->obiekty[10].load(10, "bohater5.bmp", 140, 100, 0, 3, true, true, "gudbaj_sztefi", false);

	this->obiekty[11].load(11, "budynek.bmp", -400, -1000, 0, 3, true, false, "", false);
	this->obiekty[12].load(12, "budynek1.bmp", 40, -1400, 0, 3, true, false, "", false);
	this->obiekty[13].load(13, "budynek2.bmp", 400, -1800, 0, 3, true, false, "", false);
	this->obiekty[14].load(14, "budynek3.bmp", 200, 20, -800, 3, true, false, "", false);
	this->obiekty[15].load(15, "budynek4.bmp", -400, -600, 0, 3, true, false, "", false);
	this->obiekty[16].load(16, "budynek5.bmp", 800, -1000, 0, 3, true, false, "", false);

	this->obiekty[17].load(17, "latarnia.bmp", 100, -2000, 0, 3, false, false, "", false);
	this->obiekty[18].load(18, "latarnia.bmp", 100, -2300, 0, 3, false, false, "", false);
	this->obiekty[19].load(19, "latarnia.bmp", 100, -2600, 0, 3, false, false, "", false);
	this->obiekty[20].load(20, "latarnia.bmp", 100, -2900, 0, 3, false, false, "", false);
	this->obiekty[21].load(21, "latarnia.bmp", 100, -3200, 0, 3, false, false, "", false);
	this->obiekty[22].load(22, "latarnia.bmp", 100, -3500, 0, 3, false, false, "", false);
	this->obiekty[23].load(23, "latarnia.bmp", 100, -3800, 0, 3, false, false, "", false);
	this->obiekty[24].load(24, "latarnia.bmp", 100, -4100, 0, 3, false, false, "", false);
	this->obiekty[25].load(25, "latarnia.bmp", 100, -4400, 0, 3, false, false, "", false);
	this->obiekty[26].load(26, "latarnia.bmp", 100, -4700, 0, 3, false, false, "", false);
	this->obiekty[27].load(27, "latarnia.bmp", -100, -4800, 0, 3, false, false, "", false);
	this->obiekty[28].load(28, "latarnia.bmp", -200, -5000, 0, 3, false, false, "", false);
	this->obiekty[29].load(29, "latarnia.bmp", -400, -5200, 0, 3, false, false, "", false);
	this->obiekty[30].load(30, "latarnia.bmp", -700, -5300, 0, 3, false, false, "", false);
	this->obiekty[31].load(31, "latarnia.bmp", -900, -5400, 0, 3, false, false, "", false);
	this->obiekty[32].load(32, "latarnia.bmp", -1200, -5400, 0, 3, false, false, "", false);
	this->obiekty[33].load(33, "latarnia.bmp", -1500, -5400, 0, 3, false, false, "", false);
	this->obiekty[34].load(34, "latarnia.bmp", -1800, -5400, 0, 3, false, false, "", false);
	this->obiekty[35].load(35, "latarnia.bmp", -2100, -5400, 0, 3, false, false, "", false);
	this->obiekty[36].load(36, "latarnia.bmp", -2400, -5400, 0, 3, false, false, "", false);
	this->obiekty[37].load(37, "latarnia.bmp", -2700, -5400, 0, 3, false, false, "", false);

	gameItems->initiate(player, 33);
	gameItems->items[0].copy(this->obiekty[6]);
	gameItems->items[1].copy(this->obiekty[7]);
	gameItems->items[2].copy(this->obiekty[8]);
	gameItems->items[3].copy(this->obiekty[9]);
	gameItems->items[4].copy(this->obiekty[9]);
	gameItems->items[5].copy(this->obiekty[10]);
	gameItems->items[6].copy(this->obiekty[11]);
	gameItems->items[7].copy(this->obiekty[12]);
	gameItems->items[8].copy(this->obiekty[13]);
	gameItems->items[9].copy(this->obiekty[14]);
	gameItems->items[10].copy(this->obiekty[15]);
	gameItems->items[11].copy(this->obiekty[16]);
	gameItems->items[12].copy(this->obiekty[17]);
	gameItems->items[13].copy(this->obiekty[18]);
	gameItems->items[14].copy(this->obiekty[19]);
	gameItems->items[15].copy(this->obiekty[20]);
	gameItems->items[16].copy(this->obiekty[21]);
	gameItems->items[17].copy(this->obiekty[22]);
	gameItems->items[18].copy(this->obiekty[23]);
	gameItems->items[19].copy(this->obiekty[24]);
	gameItems->items[20].copy(this->obiekty[25]);
	gameItems->items[21].copy(this->obiekty[26]);
	gameItems->items[22].copy(this->obiekty[27]);
	gameItems->items[23].copy(this->obiekty[28]);
	gameItems->items[24].copy(this->obiekty[29]);
	gameItems->items[25].copy(this->obiekty[30]);
	gameItems->items[26].copy(this->obiekty[31]);
	gameItems->items[27].copy(this->obiekty[32]);
	gameItems->items[28].copy(this->obiekty[33]);
	gameItems->items[29].copy(this->obiekty[34]);
	gameItems->items[30].copy(this->obiekty[35]);
	gameItems->items[31].copy(this->obiekty[36]);
	gameItems->items[32].copy(this->obiekty[37]);



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
