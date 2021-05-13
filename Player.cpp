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

	load("bohater.png", 600, 360, 0.2, 0, Obiekt::INTERACTION_TYPE_NONE, 0);
	sprite->setScale(0.15, 0.15);

	xPos = 0;
	yPos = 0;
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
	texture = obiekt.texture;
	sprite = obiekt.sprite;
	predkosc = obiekt.predkosc;
	warstwa = obiekt.warstwa;
	startX = obiekt.startX;
	startY = obiekt.startY;
	isVisible = obiekt.isVisible;
	height = obiekt.height;
	width = obiekt.width;

	xPos = *startX;
	yPos = *startY;
}