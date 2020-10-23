#pragma once

#include "Obiekt.h"

class Player :public Obiekt{


public:

	bool moveTop;
	bool moveBot;
	bool moveLeft;
	bool moveRight;

	bool collisionTop;
	bool collisionBot;
	bool collisionLeft;
	bool collisionRight;

	float xPos;
	float yPos;

	Player();

	void copy(Obiekt &obiekt);
	void sterowanie();
};