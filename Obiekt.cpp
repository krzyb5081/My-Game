#include "Obiekt.h"


void Obiekt::load(const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa, int interactionType, int interactionData){
	this->texture = new sf::Texture;
	this->sprite = new sf::Sprite;

	this->predkosc = new float;
	this->warstwa = new int;
	this->startX = new float;
	this->startY = new float;
	this->isVisible = new bool;
	this->isBehindScene = new bool;
	this->width = new float;
	this->height = new float;
	this->interactionType = new int;
	this->interactionData = new int;


    this->texture->loadFromFile(nazwaTextury);
    this->sprite->setTexture(*texture);
	this->sprite->setPosition(startX, startY);

	*this->predkosc = predkosc;
	*this->warstwa = warstwa;
	*this->startX = startX;
	*this->startY = startY;
	*this->isVisible = true;
	*this->isBehindScene = false;
	*this->width = (sprite->getTexture()->getSize().x)*(sprite->getScale().x);
	*this->height = (sprite->getTexture()->getSize().y)*(sprite->getScale().y);
	*this->interactionType = interactionType;
	*this->interactionData = interactionData;

	
	
}

void Obiekt::copy(Obiekt &obiekt){
	texture = obiekt.texture;
	sprite = obiekt.sprite;
	predkosc = obiekt.predkosc;
	warstwa = obiekt.warstwa;
	startX = obiekt.startX;
	startY = obiekt.startY;
	isVisible = obiekt.isVisible;
	isBehindScene = obiekt.isBehindScene;
	width = obiekt.width;
	height = obiekt.height;
	interactionType = obiekt.interactionType;
	interactionData = obiekt.interactionData;
}

void Obiekt::move(float x, float y){
	sprite->move(x, y);
}

void Obiekt::setScale(float scaleX, float scaleY){
	sprite->setScale(scaleX, scaleY);
	*this->width = (sprite->getTexture()->getSize().x)*(sprite->getScale().x);
	*this->height = (sprite->getTexture()->getSize().y)*(sprite->getScale().y);
}