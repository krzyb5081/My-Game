#include "Player.h"

Player::Player(){

	this->moveTop = false;
	this->moveBot = false;
	this->moveLeft = false;
	this->moveRight = false;

	this->collisionTop = false;
	this->collisionBot = false;
	this->collisionLeft = false;
	this->collisionRight = false;

	this->worldPlayerCoordinatesX = 0;
	this->worldPlayerCoordinatesY = 0;

	this->use = new bool(false);
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

void Player::loop() {
	this->sterowanie();

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

	this->moveTop = false;
	this->moveBot = false;
	this->moveLeft = false;
	this->moveRight = false;
	*this->use = false;

	if (!collisionTop) {
		if (keyboard.isKeyPressed(sf::Keyboard::Up)) {
			this->moveTop = true;
			worldPlayerCoordinatesY -= *predkosc;
		}
	}
	if (!collisionBot) {
		if (keyboard.isKeyPressed(sf::Keyboard::Down)) {
			this->moveBot = true;
			worldPlayerCoordinatesY += *predkosc;
		}
	}
	if (!collisionLeft) {
		if (keyboard.isKeyPressed(sf::Keyboard::Left)) {
			this->moveLeft = true;
			worldPlayerCoordinatesX -= *predkosc;
		}
	}
	if (!collisionRight) {
		if (keyboard.isKeyPressed(sf::Keyboard::Right)) {
			this->moveRight = true;
			worldPlayerCoordinatesX += *predkosc;
		}
	}
	if (keyboard.isKeyPressed(sf::Keyboard::E)) {
		*this->use = true;
	}
}