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

	this->text[0].setFillColor(sf::Color::Yellow);
	this->text[1].setFillColor(sf::Color::Yellow);

	this->text[0].setString("");
	this->text[1].setString("Press space to continue...");

	this->dialogStrings = new std::string[2];//do usuwania bloku stringow w loadDialog
	this->ktoryText = 0;

	this->spaceClickedOnce = false;
	this->dialogContinues = true;


	loadDialog(dialogId);
}

void Dialog::main(sf::RenderWindow & window) {
	this->sterowanie();
	this->rysuj(window);
	
}

void Dialog::rysuj(sf::RenderWindow & window) {
	sf::Texture texture;
	texture.loadFromFile("title screen.bmp");
	sf::Sprite sprite(texture);
	sprite.setScale(1.2, 1.3);

	window.draw(sprite);
	
	window.draw(text[0]);
	window.draw(text[1]);
}

void Dialog::sterowanie() {
	sf::Keyboard keyboard;

	if (keyboard.isKeyPressed(sf::Keyboard::Space)) {
		this->spaceClickedOnce = true;
	}
	else if (this->spaceClickedOnce) {
		this->spaceClickedOnce = false;
		this->doDialog();
	}
}

void Dialog::doDialog() {
	if (this->ktoryText >= this->ileDialogTextow) {
		this->ktoryText = 0;
		this->dialogContinues = false;
	}
	else {
 		this->text[0].setString(this->dialogStrings[this->ktoryText]);
		this->ktoryText++;
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
