#include <iostream>
#include <SFML/Graphics.hpp>

#include "Gra.h"


using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1440,900),"Save Dino Pimpus",sf::Style::Fullscreen);
	window.setFramerateLimit(140);

    Gra gra;

    sf::Event event;
    while (window.isOpen()){//**********************petla glowna************************//
		
		window.clear();
		window.pollEvent (event);
		if (event.type == sf::Event::Closed) {
			window.close();
		}
        
		gra.main(window);

		window.display();
    }
    cout << "Gra wylaczona!" << endl;
    return 0;
}
