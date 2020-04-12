#include "Obiekt.h"

Obiekt::Obiekt(){
	texture = new sf::Texture;
	sprite = new sf::Sprite;
	predkosc = new float;
	warstwa = new int;
	startX = new float;
	startY = new float;
	isVisible = new bool;
	
	*predkosc = 0;
	*warstwa = 0;
	*startX = 0;
	*startY = 0;
	*isVisible = true;
}


void Obiekt::load(const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa){
    texture->loadFromFile(nazwaTextury);
    sprite->setTexture(*texture);
	sprite->setPosition(startX, startY);

	*this->startX = startX;
	*this->startY = startY;
	*this->predkosc = predkosc;
	*this->warstwa = warstwa;
}

void Obiekt::copy(Obiekt &obiekt){
	texture = obiekt.texture;
	sprite = obiekt.sprite;
	predkosc = obiekt.predkosc;
	warstwa = obiekt.warstwa;
	startX = obiekt.startX;
	startY = obiekt.startY;
	isVisible = obiekt.isVisible;
}

void Obiekt::move(float x, float y){
	sprite->move(x, y);
}