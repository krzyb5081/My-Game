#include "Player.h"

Player::Player(){

	moveTop = false;
	moveBot = false;
	moveLeft = false;
	moveRight = false;

	collisionTop = false;
	collisionBot = false;
	collisionLeft = false;
	collisionRight = false;

	worldPlayerCoordinatesX = 0;
	worldPlayerCoordinatesY = 0;

	isTransparent = new bool(false);
}

void Player::loop() {
	this->sterowanie();
	this->makePlayerTransparent();

}


void Player::copy(Obiekt &obiekt){
	this->texture = obiekt.texture;
	this->sprite = obiekt.sprite;
	this->idNumber = obiekt.idNumber;
	this->predkosc = obiekt.predkosc;
	this->warstwa = obiekt.warstwa;
	this->isVisible = obiekt.isVisible;
	this->height = obiekt.height;
	this->width = obiekt.width;

	//pozycje startowe raczej do niczego nie potrzebne ale by byc dokladnym mozna napisac bo startowe kordy playera na swiecie to 0x0
	this->startX = new float(0);
	this->startY = new float(0);
	
	worldPlayerCoordinatesX = 0;
	worldPlayerCoordinatesY = 0;

	this->setSpritePosition(*obiekt.startX, *obiekt.startY);
	
}

bool Player::isObiectAPlayer(Obiekt & obiekt) {
	if (*this->idNumber == *obiekt.idNumber) {
		return true;
	}
	else {
		return false;
	}
}

void Player::sterowanie() {

	sf::Keyboard keyboard;

	moveTop = false;
	moveBot = false;
	moveLeft = false;
	moveRight = false;

	if (!collisionTop) {
		if (keyboard.isKeyPressed(sf::Keyboard::Up)) {
			moveTop = true;
			worldPlayerCoordinatesY -= *predkosc;
		}
	}
	if (!collisionBot) {
		if (keyboard.isKeyPressed(sf::Keyboard::Down)) {
			moveBot = true;
			worldPlayerCoordinatesY += *predkosc;
		}
	}
	if (!collisionLeft) {
		if (keyboard.isKeyPressed(sf::Keyboard::Left)) {
			moveLeft = true;
			worldPlayerCoordinatesX -= *predkosc;
		}
	}
	if (!collisionRight) {
		if (keyboard.isKeyPressed(sf::Keyboard::Right)) {
			moveRight = true;
			worldPlayerCoordinatesX += *predkosc;
		}
	}
}

void Player::makePlayerTransparent() {
	if (*this->isTransparent == true) {
		this->sprite->setColor(sf::Color(70, 70, 70, 180));
	}
	else {
		this->sprite->setColor(sf::Color(255, 255, 255, 255));
	}
}