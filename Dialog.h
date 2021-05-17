#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Dialog {
	sf::Font czcionka;
	sf::Text * text;
	std::string * dialogTexts;

public:
	void rysuj(sf::RenderWindow & window);
	void setDialog(std::string dialogId);//


	Dialog();

};

