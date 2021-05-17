#include "Dialog.h"

Dialog::Dialog() {
	if (!czcionka.loadFromFile("FORNEVER.otf")) {
		std::cout << "Nie udalo sie zaladowac czcionki." << std::endl;
	}

	this->text = new sf::Text[2];
	this->text[0].setFont(czcionka);
	this->text[1].setFont(czcionka);

	this->dialogTexts = new std::string;

}

void Dialog::setDialog(std::string dialogId) {
	sf::FileInputStream file;
	if (!file.open("dialog.txt")) {
		std::cout << "Nie udalo sie otworzyc dialogow" << std::endl;
		return;
	}
	long long dialogFileSize = file.getSize();
	char * buffer = new char[dialogFileSize];

	file.read(buffer, dialogFileSize);
	
	std::string stringBuffer(buffer);

	std::cout << stringBuffer << std::endl;

	std::cout << stringBuffer.find("TEXT", 0) << std::endl;
	stringBuffer.


	delete[] buffer;
}

void Dialog::rysuj(sf::RenderWindow & window) {

}