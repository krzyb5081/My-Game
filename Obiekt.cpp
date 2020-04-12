#include "Obiekt.h"

Obiekt::Obiekt(){
	texture = new sf::Texture;
	sprite = new sf::Sprite;

	predkosc = new float;
	warstwa = new int;
	startX = new float;
	startY = new float;
	isVisible = new bool;
	width = new float;
	height = new float;
	
	*predkosc = 0;
	*warstwa = 0;
	*startX = 0;
	*startY = 0;
	*isVisible = true;
	*width = 0;
	*height = 0;
}


void Obiekt::load(const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa){
    texture->loadFromFile(nazwaTextury);
    sprite->setTexture(*texture);
	sprite->setPosition(startX, startY);

	*this->predkosc = predkosc;
	*this->warstwa = warstwa;
	*this->startX = startX;
	*this->startY = startY;
	*this->isVisible = true;
	*this->width = (sprite->getTexture()->getSize().x)*(sprite->getScale().x);
	*this->height = (sprite->getTexture()->getSize().y)*(sprite->getScale().y);

	
	
}

void Obiekt::copy(Obiekt &obiekt){
	texture = obiekt.texture;
	sprite = obiekt.sprite;
	predkosc = obiekt.predkosc;
	warstwa = obiekt.warstwa;
	startX = obiekt.startX;
	startY = obiekt.startY;
	isVisible = obiekt.isVisible;
	width = obiekt.width;
	height = obiekt.height;
}

void Obiekt::move(float x, float y){
	sprite->move(x, y);
}

void Obiekt::setScale(float scaleX, float scaleY){
	sprite->setScale(scaleX, scaleY);
	*this->width = (sprite->getTexture()->getSize().x)*(sprite->getScale().x);
	*this->height = (sprite->getTexture()->getSize().y)*(sprite->getScale().y);
}