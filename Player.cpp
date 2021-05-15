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

	xPos = 0;
	yPos = 0;

	isTransparent = false;
}

void Player::sterowanie(){
	
	sf::Keyboard keyboard;

	moveTop = false;
	moveBot = false;
	moveLeft = false;
	moveRight = false;

	if (!collisionTop) {
		if (keyboard.isKeyPressed(sf::Keyboard::Up)) {
			moveTop = true;
			yPos -= *predkosc;
		}
	}
	if (!collisionBot) {
		if (keyboard.isKeyPressed(sf::Keyboard::Down)) {
			moveBot = true;
			yPos += *predkosc;
		}
	}
	if (!collisionLeft) {
		if (keyboard.isKeyPressed(sf::Keyboard::Left)) {
			moveLeft = true;
			xPos -= *predkosc;
		}
	}
	if (!collisionRight) {
		if (keyboard.isKeyPressed(sf::Keyboard::Right)) {
			moveRight = true;
			xPos += *predkosc;
		}
	}
}


void Player::copy(Obiekt &obiekt){
	this->texture = obiekt.texture;
	this->sprite = obiekt.sprite;
	this->idNumber = obiekt.idNumber;
	this->predkosc = obiekt.predkosc;
	this->warstwa = obiekt.warstwa;
	this->startX = obiekt.startX;
	this->startY = obiekt.startY;
	this->isVisible = obiekt.isVisible;
	this->height = obiekt.height;
	this->width = obiekt.width;

	/*//
	xPos = *startX;
	yPos = *startY;
	*/
}

bool Player::isObiectAPlayer(Obiekt & obiekt) {
	if (*this->idNumber == *obiekt.idNumber) {
		return true;
	}
	else {
		return false;
	}
}