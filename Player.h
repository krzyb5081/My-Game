#pragma once

#include "Obiekt.h"

class Player :public Obiekt{


public:

	bool naKrawedziTop;
	bool naKrawedziDown;
	bool naKrawedziLeft;
	bool naKrawedziRight;

	float xPos;
	float yPos;

	Player();

	void copy(Obiekt &obiekt);
	void sterowanie();
};