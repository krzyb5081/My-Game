#include "Background.h"

Background::Background(){
	this->initiate(new Player, 0, 0);
}

Background::Background(Player * player, int iloscObiektow, int sceneObiectIdNumber){
	this->initiate(player, iloscObiektow, sceneObiectIdNumber);
}

void Background::initiate(Player * player, int iloscObiektow, int sceneObiectIdNumber){
	obiekty = new Obiekt[iloscObiektow];

	this->player = player;
	this->iloscObiektow = iloscObiektow;
	this->sceneObiectIdNumber = sceneObiectIdNumber;

	this->sceneRectWidth = 400;
	this->sceneRectHeight = 100;


}

void Background::sterowanie() {
	

	for (int i = 0; i < iloscObiektow; i++) {
		if (*this->obiekty[i].idNumber == this->sceneObiectIdNumber) {
			this->sterowanieScena(i);
		}

		if (player->moveTop == true) {
			obiekty[i].move(0, -*obiekty[i].predkosc);
		}
		if (player->moveBot == true) {
			obiekty[i].move(0, *obiekty[i].predkosc);
		}
		if (player->moveLeft == true) {
			obiekty[i].move(*obiekty[i].predkosc, 0);
		}
		if (player->moveRight == true) {
			obiekty[i].move(-*obiekty[i].predkosc, 0);
		}

	}
}

void Background::sterowanieScena(int scenaObiektIndex) {
	sf::Vector2u textureSize = this->obiekty[scenaObiektIndex].sprite->getTexture()->getSize();
	sf::Vector2f sceneSpriteScale = this->obiekty[scenaObiektIndex].sprite->getScale();
	sf::IntRect sceneRect = this->obiekty[scenaObiektIndex].sprite->getTextureRect();

	sceneRect.width = this->sceneRectWidth;
	sceneRect.height = this->sceneRectHeight;
	
	//ustawianie prostokata idealnie na srodku
	sceneRect.left = (textureSize.x / 2) - (sceneRect.width / 2);
	sceneRect.top = (textureSize.y / 2) - (sceneRect.height / 2);

	//przesuwanie prostokata wg pozycji gracza na mapie uwzgledniajac skale spritea sceny
	sceneRect.left += this->player->worldPlayerCoordinatesX / sceneSpriteScale.x;
	sceneRect.top += this->player->worldPlayerCoordinatesY / sceneSpriteScale.y;

	this->obiekty[scenaObiektIndex].sprite->setTextureRect(sceneRect);
}