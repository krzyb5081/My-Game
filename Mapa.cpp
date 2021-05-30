#include "Mapa.h"

#include <iostream>

Mapa::Mapa(){}

Mapa::Mapa(std::string mapFile, Player * player, Collision * collision, Background * background, GameItems * gameItems){
	loadMap(mapFile, player, collision, background, gameItems);
}

void Mapa::loadMap(std::string mapFile, Player * player, Collision * collision, Background * background, GameItems * gameItems){
	
	if (mapFile == "") {
		printf("No map loaded, please exit game\n");
		while (1) {}
		return;
	}

	sf::FileInputStream file;
	if (!file.open(mapFile)) {
		printf("No map loaded, problem with opening file, please exit game\n");
		while (1) {}
		return;
	}

	//wstukanie pliku do stringa
	char * buffer = new char[file.getSize()];
	file.read(buffer, file.getSize());
	std::string stringBuffer(buffer);
	delete[] buffer;


	//na potem //usunac to
	//pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	//pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);

	int pozycjaWStringu = 0;
	int pozycjaSpacji = 0;
	int pozycjaKoncaLinii = 0;


	//////////////////////////////////////////////CZYTANIE DANYCH//////////////////////////////////////////
	
	// ustawianie wlasciwosci mapy ////////////////////////////////////////////////////////////////////////

	//wielkoscX
	pozycjaWStringu = stringBuffer.find("SIZE_X: ", pozycjaWStringu);
	pozycjaWStringu += 8;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	this->wielkoscX = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));

	//wielkoscY
	pozycjaWStringu = stringBuffer.find("SIZE_Y: ", pozycjaWStringu);
	pozycjaWStringu += 8;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	this->wielkoscY = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));

	//najwyzszaWarstwa
	pozycjaWStringu = stringBuffer.find("TOP_LAYER: ", pozycjaWStringu);
	pozycjaWStringu += 11;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	this->najwyzszaWarstwa = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));

	//iloscObiektow
	pozycjaWStringu = stringBuffer.find("OBIECTS_AMOUT: ", pozycjaWStringu);
	pozycjaWStringu += 15;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	this->iloscObiektow = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));
	
	//tworzenie tablicy obiektow
	this->obiekty = new Obiekt[this->iloscObiektow];

	
	// LOADING PLAYER /////////////////////////////////////////////////////////////////////////////////////
	
	//"PLAYER: "
	pozycjaWStringu = stringBuffer.find("PLAYER: ", pozycjaWStringu);
	pozycjaWStringu += 8;

	//idNumber
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	int idNumber = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));
	
	//nazwaTextury
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	std::string nazwaTextury = stringBuffer.substr(pozycjaWStringu, pozycjaSpacji-pozycjaWStringu);

	//startX
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	float startX = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

	//startY
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	float startY = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

	//predkosc
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	float predkosc = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

	//warstwa
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	int warstwa = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

	//colides
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	bool colides = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

	//interacts
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	bool interacts = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

	//interactionData
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	std::string interactionData = stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu);

	//isFlat
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
	bool isFlat = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

	//isBehindScene
	pozycjaWStringu = pozycjaSpacji + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	bool isBehindScene = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));
	

	//tworzenie i kopiowanie obiektu
	this->obiekty[idNumber].load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);

	player->copy(this->obiekty[0]);
	this->player = player;

	// LOADING BACKGROUND /////////////////////////////////////////////////////////////////////////////////

	//backgroundIlosc
	pozycjaWStringu = stringBuffer.find("BACKGROUND_AMOUNT: ", pozycjaWStringu);
	pozycjaWStringu += 19;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	int backgroundIlosc = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));

	background->initiate(player, backgroundIlosc);

	//obiekty background
	for (int i = 0; i < backgroundIlosc; i++) {
		//"BACKGROUND: "
		pozycjaWStringu = stringBuffer.find("BACKGROUND: ", pozycjaWStringu);
		pozycjaWStringu += 12;

		//idNumber
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		int idNumber = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//nazwaTextury
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		std::string nazwaTextury = stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu);

		//startX
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		float startX = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//startY
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		float startY = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//predkosc
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		float predkosc = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//warstwa
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		int warstwa = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//colides
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		bool colides = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//interacts
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		bool interacts = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//interactionData
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		std::string interactionData = stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu);

		//isFlat
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		bool isFlat = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//isBehindScene
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
		bool isBehindScene = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));


		//tworzenie i kopiowanie obiektow
		this->obiekty[idNumber].load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);
	
		background->obiekty[i].copy(this->obiekty[idNumber]);
	}
	
	// LOADING GAMEITEMS //////////////////////////////////////////////////////////////////////////////////

	//gameItemsIlosc
	pozycjaWStringu = stringBuffer.find("GAMEITEMS_AMOUNT: ", pozycjaWStringu);
	pozycjaWStringu += 18;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	int gameItemsIlosc = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));

	gameItems->initiate(player, gameItemsIlosc);

	//obiekty background
	for (int i = 0; i < gameItemsIlosc; i++) {
		//"GAMEITEM: "
		pozycjaWStringu = stringBuffer.find("GAMEITEM: ", pozycjaWStringu);
		pozycjaWStringu += 10;

		//idNumber
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		int idNumber = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//nazwaTextury
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		std::string nazwaTextury = stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu);

		//startX
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		float startX = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//startY
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		float startY = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//predkosc
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		float predkosc = std::stof(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//warstwa
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		int warstwa = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//colides
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		bool colides = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//interacts
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		bool interacts = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//interactionData
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		std::string interactionData = stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu);

		//isFlat
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaSpacji = stringBuffer.find(" ", pozycjaWStringu);
		bool isFlat = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaSpacji - pozycjaWStringu));

		//isBehindScene
		pozycjaWStringu = pozycjaSpacji + 1;
		pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
		bool isBehindScene = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));


		//tworzenie i kopiowanie obiektow
		this->obiekty[idNumber].load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);

		gameItems->items[i].copy(this->obiekty[idNumber]);
	}

	// LOADING GAMEITEMS TO COLLISION /////////////////////////////////////////////////////////////////////
	collision->load(player, gameItems->items, gameItems->iloscItems);

	//CHECKING GAMEITEMS VISIBILITY ///////////////////////////////////////////////////////////////////////
	gameItems->checkingVisibility();
}

Obiekt * Mapa::sortowanieObiektow(){
	
	//najdalsza warstwa lezy za scena, czyli plansz¹ po której chodzi gracz, jezeli obiekt ma warstwê 12 ale ma ustawiony parametr isBehindScene na true to bêdzie pierwszy w sortowaniu przed warstw¹ 0. Dziêki temu ka¿dy obiekt zachowa swoj¹ warstwê nawet za scen¹, sprawi to ze obiekty stojace jeden na drugim beda wychodzic zza sceny w odpowiedniej kolejnosci
	Obiekt *posortowaneObiekty = new Obiekt[this->iloscObiektow];
	int iloscPosortowanychObiektow = 0;
	

	//rozpoznawanie ktory obiekt jest obiektem playera
	int indexObiektuPlayeraWNieposortowanychObiektach = 0;
	for(int i = 0; i < this->iloscObiektow; i++) {
		if (this->player->isObiectAPlayer(this->obiekty[i])) {
			indexObiektuPlayeraWNieposortowanychObiektach = i;
			break;
		}
	}

	//sortowanie najpierw obiektow za scena (parametr isBehindScene == true)
	for (int warstwa = 0; warstwa <= this->najwyzszaWarstwa; warstwa++) {
		for (int i = 0; i < this->iloscObiektow; i++){
			if ((*this->obiekty[i].isBehindScene == true) && (*this->obiekty[i].isFlat == false)) {
				if (*this->obiekty[i].warstwa == warstwa) {
					posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty[i]);
					iloscPosortowanychObiektow++;
				}
			}
		}
	}
	//sortowanie obiektow przed scena i plaskich (parametr isBehindScene == false albo parametr isFlat == true)
	for (int warstwa = 0; warstwa <= this->najwyzszaWarstwa; warstwa++) {
		for (int i = 0; i < this->iloscObiektow; i++) {
			if (i == indexObiektuPlayeraWNieposortowanychObiektach) {//jesli teraz leci warstwa playera i index playera to pomin go zeby wrzucic go do tej warstwy na koncu, to sprawi ze na pewno bedzie przed wszystkimi obiektami danej warstwy
				continue;
			}
			if ((*this->obiekty[i].isBehindScene == false) || (*this->obiekty[i].isFlat == true)) {
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