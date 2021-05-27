#pragma once

#include "Obiekt.h"

class Player :public Obiekt{
private:
	void sterowanie();

public:

	bool moveTop;
	bool moveBot;
	bool moveLeft;
	bool moveRight;

	bool collisionTop;
	bool collisionBot;
	bool collisionLeft;
	bool collisionRight;

	float worldPlayerCoordinatesX;
	float worldPlayerCoordinatesY;

	bool * use;

	Player();

	void copy(Obiekt &obiekt);
	void loop();
	bool isObiectAPlayer(Obiekt & obiekt);



};