#include "Menu.h"

Menu::Menu() {
    if(!czcionka.loadFromFile("FORNEVER.otf")) {
        cout << "Nie udalo sie zaladowac czcionki." << endl;
    }

    menuText[0].setFont(czcionka);
    menuText[0].setString("Start");
    menuText[0].setPosition(50,50);
    menuText[1].setFont(czcionka);
    menuText[1].setString("Randomowe informacje");
    menuText[1].setPosition(50,150);
    menuText[2].setFont(czcionka);
    menuText[2].setString("Wyjscie");
    menuText[2].setPosition(50,250);

    ktoraOpcja = 0;
    bylPuszczonyUp = false;
    bylPuszczonyDown = false;
}

int Menu::zmienianieOpcji(sf::RenderWindow & window) {
    if((klawiatura.isKeyPressed(sf::Keyboard::Up))&&(bylPuszczonyUp)){
        bylPuszczonyUp = false;
        if(ktoraOpcja==0){
            ktoraOpcja = sizeof(menuText)/sizeof(sf::Text)-1;
        }
        else {
            ktoraOpcja--;
        }
    }
    else if(!klawiatura.isKeyPressed(sf::Keyboard::Up)) {
        bylPuszczonyUp = true;
    }
    if((klawiatura.isKeyPressed(sf::Keyboard::Down))&&(bylPuszczonyDown)){
        bylPuszczonyDown = false;
        if(ktoraOpcja==sizeof(menuText)/sizeof(sf::Text)-1) {
            ktoraOpcja = 0;
        }
        else {
                ktoraOpcja++;
        }
    }
    else if(!klawiatura.isKeyPressed(sf::Keyboard::Down)) {
        bylPuszczonyDown = true;
    }
    if(klawiatura.isKeyPressed(sf::Keyboard::Return)) {//ENTER

        //window.clear(sf::Color(133,33,137));


        if(ktoraOpcja==2) {//wyjscie
            window.close();
        }
        return ktoraOpcja;
    }

    return -1;
}


void Menu::rysowanieMenu(sf::RenderWindow & window) {
	sf::Texture texture;
	texture.loadFromFile("title screen.bmp");
	sf::Sprite sprite(texture);
	sprite.setScale(1.1, 1.2);

	window.draw(sprite);
    for(unsigned int i=0;i<sizeof(menuText)/sizeof(sf::Text);i++){
        menuText[i].setFillColor(sf::Color::Yellow);
        if((int)i==ktoraOpcja){
            menuText[i].setFillColor(sf::Color::Red);
        }
        window.draw(menuText[i]);
    }
}
