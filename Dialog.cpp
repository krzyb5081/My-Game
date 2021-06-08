#include "Dialog.h"

Dialog::Dialog() {
	load("");
}

void Dialog::load(std::string dialogId) {
	
	if (!czcionka.loadFromFile("FORNEVER.otf")) {
		std::cout << "Nie udalo sie zaladowac czcionki." << std::endl;
	}

	this->text = new sf::Text[2];
	this->text[0].setFont(czcionka);
	this->text[1].setFont(czcionka);

	this->text[0].setPosition(100, 600);
	this->text[1].setPosition(600, 800);

	this->text[0].setFillColor(sf::Color::Cyan);
	this->text[1].setFillColor(sf::Color::Cyan);

	this->text[0].setString("");
	this->text[1].setString("Press space to continue...");

	this->dialogStrings = new std::string[2];//zeby delete[] moglo usunac blok danych w loadDialog (sprawdzic czy to musi byc blok bo nie wiem)
	this->numerWyswietlanegoTextu = 0;

	this->spacePressedOnce = false;
	this->dialogContinues = true;


	loadDialog(dialogId);
	doDialog();
}

void Dialog::main(sf::RenderWindow & window) {
	this->sterowanie();
	this->rysuj(window);
	
}

void Dialog::rysuj(sf::RenderWindow & window) {
	sf::Texture texture;
	texture.loadFromFile("dialog.bmp");
	sf::Sprite sprite(texture);
	sprite.setScale(1.2, 1.3);

	sf::Texture texture1;
	texture1.loadFromFile("text-background.bmp");
	sf::Sprite sprite1(texture1);
	sprite1.setPosition(0, 580);
	sprite1.setScale(2, 3.5);
	sprite1.setColor(sf::Color(60, 60, 60, 220));
	

	window.draw(sprite);
	window.draw(sprite1);
	
	window.draw(text[0]);
	window.draw(text[1]);
}

void Dialog::sterowanie() {
	sf::Keyboard keyboard;

	if (keyboard.isKeyPressed(sf::Keyboard::Space)) {
		this->spacePressedOnce = true;
	}
	else if (this->spacePressedOnce) {
		this->spacePressedOnce = false;
		this->doDialog();
	}
}

void Dialog::doDialog() {
	if (this->numerWyswietlanegoTextu >= this->ileDialogTextow) {
		this->numerWyswietlanegoTextu = 0;
		this->dialogContinues = false;
	}
	else {
 		this->text[0].setString(this->dialogStrings[this->numerWyswietlanegoTextu]);
		this->numerWyswietlanegoTextu++;
	}

 
  	
}

void Dialog::loadDialog(std::string dialogId) {
	
	delete[] this->dialogStrings;
	if (dialogId == "") {
		this->dialogStrings = new std::string[2];
		this->dialogStrings[0] = "";
		this->dialogStrings[1] = "";
		return;
	}

	sf::FileInputStream file;
	if (!file.open("dialog.txt")) {
		std::cout << "Nie udalo sie otworzyc pliku dialogow" << std::endl;
		return;
	}

	//wstukanie pliku do bufora
	char * buffer = new char[file.getSize()];
	file.read(buffer, file.getSize());
	std::string stringBuffer(buffer);
	delete[] buffer;

	//wyszukanie dialogu w buforze
	int pozycjaPoczatkuDialogu = stringBuffer.find("DIALOG_ID: "+dialogId, 0);
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
		else if(pozycjaTekstu != pozycjaOstatniegoTekstu){
			iloscZnakowWTekscie = stringBuffer.find("TEXT: ", pozycjaTekstu) - pozycjaTekstu;//pozycja nastepnego tekstu - pozycja tekstu = ilosc znakow miedzy tekstam
		}

		this->dialogStrings[numerTekstu].assign(stringBuffer, pozycjaTekstu, iloscZnakowWTekscie);//od miejsca pozycji tekstu skopiowac iloscZnakowWTekscie znakow do charBuffera

	}
}
