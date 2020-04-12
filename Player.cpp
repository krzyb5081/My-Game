#include "Player.h"

Player::Player(){

	naKrawedziTop = false;
	naKrawedziDown = false;
	naKrawedziLeft = false;
	naKrawedziRight = false;

	load("bohater.png", 600, 360, 0.2, 0);
	sprite->setScale(0.15, 0.15);

	xPos = 0;
	yPos = 0;
}

void Player::sterowanie(){
	
	sf::Keyboard keyboard;

	naKrawedziTop = false;
	naKrawedziDown = false;
	naKrawedziLeft = false;
	naKrawedziRight = false;

	if (keyboard.isKeyPressed(sf::Keyboard::Up)){
		if (sprite->getPosition().y - *predkosc > 370){
			move(0, -*predkosc);
		}
		else{
			naKrawedziTop = true;
		}
		yPos -= *predkosc;
		
	}
	if (keyboard.isKeyPressed(sf::Keyboard::Down)) {
		if (sprite->getPosition().y + *predkosc < 650){
			move(0, *predkosc);
		}
		else{
			naKrawedziDown = true;
		}
		yPos += *predkosc;
		
	}
	if (keyboard.isKeyPressed(sf::Keyboard::Left)) {
		if (sprite->getPosition().x - *predkosc > 50){
			move(-*predkosc, 0);
		}
		else{
			naKrawedziLeft = true;
		}
		xPos -= *predkosc;
		
	}
	if (keyboard.isKeyPressed(sf::Keyboard::Right)) {
		if (sprite->getPosition().x + *predkosc < 1200){
			move(*predkosc, 0);
		}
		else{
			naKrawedziRight = true;
		}
		xPos += *predkosc;
		
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