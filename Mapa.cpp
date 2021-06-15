#include "Mapa.h"

#include <iostream>
#include <fstream>

Mapa::Mapa(){}// nie uzywac

Mapa::Mapa(std::string mapFile, Player * player, Collision * collision, Background * background, GameItems * gameItems){
	loadMap(mapFile, player, collision, background, gameItems);
}

void Mapa::loadMap(std::string mapFile, Player * player, Collision * collision, Background * background, GameItems * gameItems){
	
	this->player = player;
	this->collision = collision;
	this->background = background;
	this->gameItems = gameItems;

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
	this->obiekty = new std::vector<Obiekt>;

	
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

	Obiekt newObiect;
	newObiect.load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);
	this->obiekty->push_back(newObiect);

	player->copy(this->obiekty->back());

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
		Obiekt newObiect;
		newObiect.load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);
		this->obiekty->push_back(newObiect);

		background->obiekty[i].copy(this->obiekty->back());
	}
	
	// LOADING GAMEITEMS //////////////////////////////////////////////////////////////////////////////////

	//gameItemsIlosc
	pozycjaWStringu = stringBuffer.find("GAMEITEMS_AMOUNT: ", pozycjaWStringu);
	pozycjaWStringu += 18;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	int gameItemsIlosc = std::stoi(stringBuffer.substr(pozycjaWStringu, pozycjaKoncaLinii - pozycjaWStringu));

	gameItems->initiate(player, gameItemsIlosc);

	//obiekty gameItems
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
		Obiekt newObiect;
		newObiect.load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);
		this->obiekty->push_back(newObiect);

		gameItems->items->push_back(this->obiekty->back());
	}

	// LOADING GAMEITEMS TO COLLISION /////////////////////////////////////////////////////////////////////
	collision->load(player, gameItems->items, *gameItems->iloscItems);

	//CHECKING GAMEITEMS VISIBILITY ///////////////////////////////////////////////////////////////////////
	gameItems->checkingVisibility();
}

void Mapa::saveMap(std::string mapFile) {
	if (mapFile == "") {
		printf("Map is not saved\n");
		return;
	}

	std::string stringBuffer = "";


	//////////////////////////////////////////////ZAPIS DANYCH/////////////////////////////////////////////

	// wlasciwosci mapy ///////////////////////////////////////////////////////////////////////////////////

	//wielkoscX
	stringBuffer += "SIZE_X: ";
	stringBuffer += std::to_string(this->wielkoscX);
	stringBuffer += "\n";

	//wielkoscY
	stringBuffer += "SIZE_Y: ";
	stringBuffer += std::to_string(this->wielkoscY);
	stringBuffer += "\n";

	//najwyzszaWarstwa
	stringBuffer += "TOP_LAYER: ";
	stringBuffer += std::to_string(this->najwyzszaWarstwa);
	stringBuffer += "\n";

	//iloscObiektow
	stringBuffer += "OBIECTS_AMOUT: ";
	stringBuffer += std::to_string(this->iloscObiektow);
	stringBuffer += "\n";

	stringBuffer += "\n";

	// LOADING PLAYER /////////////////////////////////////////////////////////////////////////////////////

	//"PLAYER: "
	stringBuffer += "PLAYER:";
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->idNumber);
	stringBuffer += " ";
	stringBuffer += *this->player->textureName;
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->startX);
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->startY);
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->predkosc);
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->warstwa);
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->colides);
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->interacts);
	stringBuffer += " ";
	stringBuffer += *this->player->interactionData;
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->isFlat);
	stringBuffer += " ";
	stringBuffer += std::to_string(*this->player->isBehindScene);

	stringBuffer += "\n\n";

	// LOADING BACKGROUND /////////////////////////////////////////////////////////////////////////////////

	//backgroundIlosc
	stringBuffer += "BACKGROUND_AMOUNT: ";
	stringBuffer += std::to_string(*this->background->iloscObiektow);
	stringBuffer += "\n\n";

	//obiekty background
	for (int i = 0; i < *this->background->iloscObiektow; i++) {

		stringBuffer += "BACKGROUND:";
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].idNumber);
		stringBuffer += " ";
		stringBuffer += *this->background->obiekty[i].textureName;
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].startX);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].startY);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].predkosc);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].warstwa);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].colides);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].interacts);
		stringBuffer += " ";
		stringBuffer += *this->background->obiekty[i].interactionData;
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].isFlat);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->background->obiekty[i].isBehindScene);
		stringBuffer += "\n";
	}
	stringBuffer += "\n";

	// LOADING GAMEITEMS //////////////////////////////////////////////////////////////////////////////////

	//gameItemsIlosc
	stringBuffer += "GAMEITEMS_AMOUNT: ";
	stringBuffer += std::to_string(*this->gameItems->iloscItems);
	stringBuffer += "\n\n";

	//obiekty gameItems
	for (int i = 0; i < *this->gameItems->iloscItems; i++) {

		stringBuffer += "GAMEITEM:";
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).idNumber);
		stringBuffer += " ";
		stringBuffer += *this->gameItems->items->at(i).textureName;
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).startX);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).startY);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).predkosc);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).warstwa);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).colides);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).interacts);
		stringBuffer += " ";
		stringBuffer += *this->gameItems->items->at(i).interactionData;
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).isFlat);
		stringBuffer += " ";
		stringBuffer += std::to_string(*this->gameItems->items->at(i).isBehindScene);
		stringBuffer += "\n";
	}
	stringBuffer += "\n";

	std::fstream file;
	file.open(mapFile, std::ios_base::out | std::ios_base::trunc);
	file << stringBuffer;
	file.close();
	std::cout << stringBuffer << std::endl;
}

void Mapa::loadObiectFromFile(std::string obiectFile) {
	
	if (obiectFile == "") {
		printf("No obiect loaded, please exit game\n");
		while (1) {}
		return;
	}

	sf::FileInputStream file;
	if (!file.open(obiectFile)) {
		printf("No obiect loaded, problem with opening file, please exit game\n");
		while (1) {}
		return;
	}

	//wstukanie pliku do stringa
	char * buffer = new char[file.getSize()];
	file.read(buffer, file.getSize());
	std::string stringBuffer(buffer);
	delete[] buffer;


	int pozycjaWStringu = 0;
	int pozycjaPoSpacji = 0;
	int pozycjaKoncaLinii = 0;

	
	//"texture_file_name: "
	pozycjaWStringu = stringBuffer.find("texture_file_name: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	std::string nazwaTextury = stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji);
	std::cout << nazwaTextury << std::endl;
	//"start_positon_x: "
	pozycjaWStringu = stringBuffer.find("start_positon_x: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	float startX = std::stof(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << startX << std::endl;
	//"start_positon_y: "
	pozycjaWStringu = stringBuffer.find("start_positon_y: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	float startY = std::stof(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << startY << std::endl;
	//"velocity: "
	pozycjaWStringu = stringBuffer.find("velocity: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	float predkosc = std::stof(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << predkosc << std::endl;
	//"layer: "
	pozycjaWStringu = stringBuffer.find("layer: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	int warstwa = std::stoi(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << warstwa << std::endl;
	//"colides: "
	pozycjaWStringu = stringBuffer.find("colides: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	bool colides = std::stoi(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << colides << std::endl;
	//"interacts: "
	pozycjaWStringu = stringBuffer.find("interacts: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	bool interacts = std::stoi(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << interacts << std::endl;
	//"interaction_data: "
	pozycjaWStringu = stringBuffer.find("interaction_data: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	std::string interactionData = stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji);
	std::cout << interactionData << std::endl;
	//"is_flat: "
	pozycjaWStringu = stringBuffer.find("is_flat: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	bool isFlat = std::stoi(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << isFlat << std::endl;
	//"is_behind_scene: "
	pozycjaWStringu = stringBuffer.find("is_behind_scene: ", pozycjaWStringu);
	pozycjaPoSpacji = stringBuffer.find(" ", pozycjaWStringu) + 1;
	pozycjaKoncaLinii = stringBuffer.find("\n", pozycjaWStringu);
	bool isBehindScene = std::stoi(stringBuffer.substr(pozycjaPoSpacji, pozycjaKoncaLinii - pozycjaPoSpacji));
	std::cout << isBehindScene << std::endl;

	//zwiekszenie liczby obiektow
	this->iloscObiektow++;
	this->gameItems->iloscItems++;
	int idNumber = this->iloscObiektow - 1;

	//tworzenie i kopiowanie obiektow
	Obiekt newObiect;
	newObiect.load(idNumber, nazwaTextury.c_str(), startX, startY, predkosc, warstwa, colides, interacts, interactionData, isFlat, isBehindScene);
	this->obiekty->push_back(newObiect);
	
	this->gameItems->items->push_back(this->obiekty->back());
}

std::vector<Obiekt> * Mapa::sortowanieObiektow(){
	
	//najdalsza warstwa lezy za scena, czyli plansz¹ po której chodzi gracz, jezeli obiekt ma warstwê 12 ale ma ustawiony parametr isBehindScene na true to bêdzie pierwszy w sortowaniu przed warstw¹ 0. Dziêki temu ka¿dy obiekt zachowa swoj¹ warstwê nawet za scen¹, sprawi to ze obiekty stojace jeden na drugim beda wychodzic zza sceny w odpowiedniej kolejnosci
	Obiekt *posortowaneObiekty = new Obiekt[this->iloscObiektow];
	int iloscPosortowanychObiektow = 0;
	

	//rozpoznawanie ktory obiekt jest obiektem playera
	int indexObiektuPlayeraWNieposortowanychObiektach = 0;
	for(int i = 0; i < this->iloscObiektow; i++) {
		if (this->player->isObiectAPlayer(this->obiekty->at(i))) {
			indexObiektuPlayeraWNieposortowanychObiektach = i;
			break;
		}
	}

	//sortowanie najpierw obiektow za scena (parametr isBehindScene == true)
	for (int warstwa = 0; warstwa <= this->najwyzszaWarstwa; warstwa++) {
		for (int i = 0; i < this->iloscObiektow; i++){
			if ((*this->obiekty->at(i).isBehindScene == true) && (*this->obiekty->at(i).isFlat == false)) {
				if (*this->obiekty->at(i).warstwa == warstwa) {
					posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty->at(i));
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
			if ((*this->obiekty->at(i).isBehindScene == false) || (*this->obiekty->at(i).isFlat == true)) {
				if (*this->obiekty->at(i).warstwa == warstwa) {
					posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty->at(i));
					iloscPosortowanychObiektow++;
				}
			}
		}
		if (*this->obiekty->at(indexObiektuPlayeraWNieposortowanychObiektach).warstwa == warstwa) {
			posortowaneObiekty[iloscPosortowanychObiektow].copy(this->obiekty->at(indexObiektuPlayeraWNieposortowanychObiektach));
			iloscPosortowanychObiektow++;
		}
	}

	
	for (int i = 0; i < iloscPosortowanychObiektow; i++) {
		this->obiekty->at(i).copy(posortowaneObiekty[i]);
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

std::vector<Obiekt> * Mapa::getObiects(){
	return this->obiekty;
}