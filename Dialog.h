#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Dialog {
	sf::Font czcionka;
	sf::Text * text;

	std::string * dialogStrings;
	int ileDialogTextow;
	int ktoryText;

	bool spaceClickedOnce;
	
	void rysuj(sf::RenderWindow & window);
	void sterowanie();
	void doDialog();
	void loadDialog(std::string dialogId);//wczytanie dialogu z pliku

public:

	bool dialogContinues;

	void main(sf::RenderWindow & window);
	
	void load(std::string dialogId);
	


	Dialog();

};

