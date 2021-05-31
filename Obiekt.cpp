#include "Obiekt.h"


void Obiekt::load(int idNumber, const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa, bool colides, bool interacts, std::string interactionData, bool isFlat, bool isBehindScene){
	
	this->idNumber = new int;

	this->texture = new sf::Texture;
	this->sprite = new sf::Sprite;
	this->textureName = new std::string;

	this->warstwa = new int;
	this->isVisible = new bool;
	this->isBehindScene = new bool;
	this->isTransparent = new bool;

	this->predkosc = new float;
	this->startX = new float;
	this->startY = new float;
	this->width = new float;
	this->height = new float;

	this->colides = new bool;
	this->interacts = new bool;
	this->interactionData = new std::string;
	this->isFlat = new bool;


	*this->idNumber = idNumber;

    this->texture->loadFromFile(nazwaTextury);
    this->sprite->setTexture(*texture);
	this->sprite->setPosition(startX, startY);
	*this->textureName = nazwaTextury;

	*this->warstwa = warstwa;
	*this->isVisible = true;
	*this->isBehindScene = isBehindScene;
	*this->isTransparent = false;

	*this->predkosc = predkosc;
	*this->startX = startX;
	*this->startY = startY;
	*this->width = (sprite->getTexture()->getSize().x)*(sprite->getScale().x);
	*this->height = (sprite->getTexture()->getSize().y)*(sprite->getScale().y);

	*this->colides = colides;
	*this->interacts = interacts;
	*this->interactionData = interactionData;
	*this->isFlat = isFlat;

	
}

void Obiekt::copy(Obiekt &obiekt){//przy zmienianiu copy() zmienic jeszcze w playerze
	this->idNumber = obiekt.idNumber;

	this->texture = obiekt.texture;
	this->sprite = obiekt.sprite;
	this->textureName = obiekt.textureName;
	
	this->warstwa = obiekt.warstwa;
	this->isVisible = obiekt.isVisible;
	this->isBehindScene = obiekt.isBehindScene;
	this->isTransparent = obiekt.isTransparent;

	this->predkosc = obiekt.predkosc;
	this->startX = obiekt.startX;
	this->startY = obiekt.startY;
	this->width = obiekt.width;
	this->height = obiekt.height;

	this->colides = obiekt.colides;
	this->interacts = obiekt.interacts;
	this->interactionData = obiekt.interactionData;
	this->isFlat = obiekt.isFlat;
}

void Obiekt::move(float x, float y){
	sprite->move(x, y);
}

void Obiekt::setSpritePosition(float x, float y) {
	this->sprite->setPosition(x, y);
}

void Obiekt::setScale(float scaleX, float scaleY){
	this->sprite->setScale(scaleX, scaleY);
	*this->width = (sprite->getTextureRect().width)*(sprite->getScale().x);
	*this->height = (sprite->getTextureRect().height)*(sprite->getScale().y);
}

void Obiekt::makeObiectTransparent(bool isTransparent) {
	*this->isTransparent = isTransparent;

	if (*this->isTransparent == true) {
		this->sprite->setColor(sf::Color(255, 255, 255, 100));
	}
	else {
		this->sprite->setColor(sf::Color(255, 255, 255, 255));
	}
}