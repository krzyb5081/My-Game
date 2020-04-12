#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Gra.h"


/*/////////////////////////////////////////////////////////////////////
*
*
* 
*
*
*
*
* 
*
*
*
*
*
*
*
*
*jak sie idzie na gore albo dol to jesli cos sie znajduje nad bohaterem w dosc dalekiej odleglosci to ma sie przesuwac w gore a potem dopiero w dol 
*
*
**////////////////////////////////////////////////////////////////////




using namespace std;
enum stan_gry {
    MENU = 0,
    GRA = 1
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400,800),"Okno gry");
	sf::Event event;

	stan_gry stan = MENU;
    Menu menu;
    Gra gra;

    
    while (window.isOpen()){//**********************petla glowna************************//
		

		window.display();
		window.clear();
		window.pollEvent (event);

        if(event.type == sf::Event::Closed){
            window.close();
        }
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
			stan = MENU;
		}


        switch(stan) {
			case MENU:
				if(menu.zmienianieOpcji(window) == 0) {
					stan = GRA;
				}
				menu.rysowanieMenu(window);
				break;
			case GRA:
				gra.loop(window);
				break;
			default:
				cout << "gra nie wie w jakim jest stanie" << endl;
				window.close();
        }


    }
    cout << "Gra wylaczona!" << endl;
    return 0;
}
