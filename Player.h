#pragma once

#include "Obiekt.h"

class Player :public Obiekt{
private:
	void sterowanie();
	void makePlayerTransparent();

public:

	bool moveTop;
	bool moveBot;
	bool moveLeft;
	bool moveRight;

	bool use;

	bool collisionTop;
	bool collisionBot;
	bool collisionLeft;
	bool collisionRight;

	float worldPlayerCoordinatesX;
	float worldPlayerCoordinatesY;

	bool * isTransparent;

	Player();

	void copy(Obiekt &obiekt);
	void loop();
	bool isObiectAPlayer(Obiekt & obiekt);



};