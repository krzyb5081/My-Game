#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Menu {

    sf::Font czcionka;
    sf::Text menuText[3];
    int ktoraOpcja;
    bool bylPuszczonyUp ,bylPuszczonyDown;

public:
    int zmienianieOpcji(sf::RenderWindow & window);
    void rysuj(sf::RenderWindow & window);


    Menu();

};