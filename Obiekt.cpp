#include "Obiekt.h"


void Obiekt::load(const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa){
	this->texture = new sf::Texture;
	this->sprite = new sf::Sprite;

	this->predkosc = new float;
	this->warstwa = new int;
	this->startX = new float;
	this->startY = new float;
	this->isVisible = new bool;
	this->width = new float;
	this->height = new float;

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