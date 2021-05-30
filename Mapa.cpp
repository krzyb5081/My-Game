#include "Mapa.h"

#include <iostream>

Mapa::Mapa(){
	loadMap("map.txt", new Player, new Collision, new Background, new GameItems);
}

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


	//na potem
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

	//idNumber
	pozycjaWStringu += 8;
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
	


	this->obiekty[0].load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);

	player->copy(this->obiekty[0]);
	this->player = player;

	




	std::cout << "liczba " << interactionData << std::endl;
	std::cout << "size: " << pozycjaWStringu << " spacja: " << pozycjaSpacji << " koniec: " << pozycjaKoncaLinii << std::endl;
	/*
	////////////////////////////////////////////////////////////////TUTAJ SKONCZYLEM
	//wyszukanie dialogu w buforze
	int pozycjaPoczatkuDialogu = stringBuffer.find("DIALOG_ID: " + dialogId, 0);
	int pozycjaKoncaDialogu = stringBuffer.find("DIALOG_END", pozycjaPoczatkuDialogu);

	int pozycjaOstatniegoTekstu = stringBuffer.rfind("TEXT: ", pozycjaKoncaDialogu) + 6;//dlugosc "TEXT: "


	//liczenie tekstow w dialogu
	int pozycjaTekstu = pozycjaPoczatkuDialogu;//zeby szukanie zaczelo sie przed pierwszym "TEXT: "
	this->ileDialogTextow = 0;
	while (pozycjaTekstu < pozycjaOstatniegoTekstu) {
		pozycjaTekstu = stringBuffer.find("TEXT: ", pozycjaTekstu);
		pozycjaTekstu += 6;//dlugosc "TEXT: "
		this->ileDialogTextow++;

	}

	//wczytywanie tekstow do zmiennych
	this->dialogStrings = new std::string[this->ileDialogTextow];
	pozycjaTekstu = pozycjaPoczatkuDialogu;//zeby szukanie zaczelo sie przed pierwszym "TEXT: "
	for (int numerTekstu = 0; numerTekstu < this->ileDialogTextow; numerTekstu++) {
		pozycjaTekstu = stringBuffer.find("TEXT: ", pozycjaTekstu);
		pozycjaTekstu += 6;//dlugosc "TEXT: "

		int iloscZnakowWTekscie;
		if (pozycjaTekstu == pozycjaOstatniegoTekstu) {
			iloscZnakowWTekscie = pozycjaKoncaDialogu - pozycjaTekstu;
		}
		else if (pozycjaTekstu != pozycjaOstatniegoTekstu) {
			iloscZnakowWTekscie = stringBuffer.find("TEXT: ", pozycjaTekstu) - pozycjaTekstu;//pozycja nastepnego tekstu - pozycja tekstu = ilosc znakow miedzy tekstam
		}
		
		this->dialogStrings[numerTekstu].assign(stringBuffer, pozycjaTekstu, iloscZnakowWTekscie);//od miejsca pozycji tekstu skopiowac iloscZnakowWTekscie znakow do charBuffera

	}
	*/
	/*
	// ustawianie wlasciwosci mapy ////////////////////////////////////////////////////////////////////////
	this->wielkoscX = 1000;
	this->wielkoscY = 1000;
	this->najwyzszaWarstwa = 20;
	this->iloscObiektow = 38;

	this->obiekty = new Obiekt[this->iloscObiektow];

	// LOADING PLAYER /////////////////////////////////////////////////////////////////////////////////////
	this->obiekty[0].load(0, "bohater.bmp", 650, 600, 1, 20, true, false, "", false, false);
	
	player->copy(this->obiekty[0]);
	this->player = player;
	*/
	// LOADING BACKGROUND /////////////////////////////////////////////////////////////////////////////////
	this->obiekty[1].load(1, "scene.bmp", 0, 450, 0, 0, false, false, "", false, false);//pierwsza zerowa warstwa 'przed scena' bo ten obiekt jest scena
	this->obiekty[2].load(2, "niebo.bmp", -400, 0, 0.01, 0, false, false, "", false, true);//za scena
	this->obiekty[3].load(3, "slonce.bmp", 210, -210, 0, 1, false, false, "", false, true);//za scena
	this->obiekty[4].load(4, "gory.bmp", -400, 200, 0.02, 2, false, false, "", false, true);//za scena

	background->initiate(player, 4, 1);//pierwszy wczytany background jest scena
	background->obiekty[0].copy(this->obiekty[1]);
	background->obiekty[1].copy(this->obiekty[2]);
	background->obiekty[2].copy(this->obiekty[3]);
	background->obiekty[3].copy(this->obiekty[4]);
	
	// LOADING GAMEITEMS //////////////////////////////////////////////////////////////////////////////////
	this->obiekty[5].load(5, "bohater.bmp", -500, 0, 0, 3, true, true, "jotpe", false, false);
	this->obiekty[6].load(6, "bohater1.bmp", -200, -100, 0, 3, true, true, "jotpe", true, false);
	this->obiekty[7].load(7, "bohater2.bmp", -200, -200, 0, 3, true, true, "halu_sztefi", true, false);
	this->obiekty[8].load(8, "bohater3.bmp", 40, 100, 0, 3, true, true, "halu_sztefi", true, false);
	this->obiekty[9].load(9, "bohater4.bmp", 200, -30, 0, 3, true, true, "gudbaj_sztefi", false, false);
	this->obiekty[10].load(10, "bohater5.bmp", 140, 100, 0, 3, true, true, "gudbaj_sztefi", false, false);

	this->obiekty[11].load(11, "budynek.bmp", -400, -1000, 0, 3, true, false, "", false, false);
	this->obiekty[12].load(12, "budynek1.bmp", 40, -1400, 0, 3, true, false, "", false, false);
	this->obiekty[13].load(13, "budynek2.bmp", 400, -1800, 0, 3, true, false, "", false, false);
	this->obiekty[14].load(14, "budynek3.bmp", 200, 20, -800, 3, true, false, "", false, false);
	this->obiekty[15].load(15, "budynek4.bmp", -400, -600, 0, 3, true, false, "", false, false);
	this->obiekty[16].load(16, "budynek5.bmp", 800, -1000, 0, 3, true, false, "", false, false);

	this->obiekty[17].load(17, "latarnia.bmp", 100, -2000, 0, 3, false, false, "", false, false);
	this->obiekty[18].load(18, "latarnia.bmp", 100, -2300, 0, 3, false, false, "", false, false);
	this->obiekty[19].load(19, "latarnia.bmp", 100, -2600, 0, 3, false, false, "", false, false);
	this->obiekty[20].load(20, "latarnia.bmp", 100, -2900, 0, 3, false, false, "", false, false);
	this->obiekty[21].load(21, "latarnia.bmp", 100, -3200, 0, 3, false, false, "", false, false);
	this->obiekty[22].load(22, "latarnia.bmp", 100, -3500, 0, 3, false, false, "", false, false);
	this->obiekty[23].load(23, "latarnia.bmp", 100, -3800, 0, 3, false, false, "", false, false);
	this->obiekty[24].load(24, "latarnia.bmp", 100, -4100, 0, 3, false, false, "", false, false);
	this->obiekty[25].load(25, "latarnia.bmp", 100, -4400, 0, 3, false, false, "", false, false);
	this->obiekty[26].load(26, "latarnia.bmp", 100, -4700, 0, 3, false, false, "", false, false);
	this->obiekty[27].load(27, "latarnia.bmp", -100, -4800, 0, 3, false, false, "", false, false);
	this->obiekty[28].load(28, "latarnia.bmp", -200, -5000, 0, 3, false, false, "", false, false);
	this->obiekty[29].load(29, "latarnia.bmp", -400, -5200, 0, 3, false, false, "", false, false);
	this->obiekty[30].load(30, "latarnia.bmp", -700, -5300, 0, 3, false, false, "", false, false);
	this->obiekty[31].load(31, "latarnia.bmp", -900, -5400, 0, 3, false, false, "", false, false);
	this->obiekty[32].load(32, "latarnia.bmp", -1200, -5400, 0, 3, false, false, "", false, false);
	this->obiekty[33].load(33, "latarnia.bmp", -1500, -5400, 0, 3, false, false, "", false, false);
	this->obiekty[34].load(34, "latarnia.bmp", -1800, -5400, 0, 3, false, false, "", false, false);
	this->obiekty[35].load(35, "latarnia.bmp", -2100, -5400, 0, 3, false, false, "", false, false);
	this->obiekty[36].load(36, "latarnia.bmp", -2400, -5400, 0, 3, false, false, "", false, false);
	this->obiekty[37].load(37, "latarnia.bmp", -2700, -5400, 0, 3, false, false, "", false, false);

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