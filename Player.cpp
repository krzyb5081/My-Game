#include "Player.h"

Player::Player(){

	naKrawedziTop = false;
	naKrawedziDown = false;
	naKrawedziLeft = false;
	naKrawedziRight = false;

	load("bohater.png", 600, 360, 0.2, 0);
	sprite->setScale(0.15, 0.15);

	xPrzesuniecie = 0;
	yPrzesuniecie = 0;
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
			yPrzesuniecie -= *predkosc;
			naKrawedziTop = true;
		}
		
	}
	if (keyboard.isKeyPressed(sf::Keyboard::Down)) {
		if (sprite->getPosition().y + *predkosc < 650){
			move(0, *predkosc);
		}
		else{
			yPrzesuniecie += *predkosc;
			naKrawedziDown = true;
		}
		
	}
	if (keyboard.isKeyPressed(sf::Keyboard::Left)) {
		if (sprite->getPosition().x - *predkosc > 50){
			move(-*predkosc, 0);
		}
		else{
			xPrzesuniecie -= *predkosc;
			naKrawedziLeft = true;
		}
		
	}
	if (keyboard.isKeyPressed(sf::Keyboard::Right)) {
		if (sprite->getPosition().x + *predkosc < 1200){
			move(*predkosc, 0);
		}
		else{
			xPrzesuniecie += *predkosc;
			naKrawedziRight = true;
		}
		
	}
}