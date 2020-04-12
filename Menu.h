#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Menu {

    sf::Font czcionka;
    sf::Text menuText[3];
    sf::Keyboard klawiatura;
    int ktoraOpcja;
    bool bylPuszczonyUp ,bylPuszczonyDown;

public:
    int zmienianieOpcji(sf::RenderWindow & window);
    void rysowanieMenu(sf::RenderWindow & window);


    Menu();

};

#endif // MENU_H
