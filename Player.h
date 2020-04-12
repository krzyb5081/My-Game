#ifndef PLAYER_H
#define PLAYER_H

#include "Obiekt.h"

class Player :public Obiekt{


public:

	bool naKrawedziTop;
	bool naKrawedziDown;
	bool naKrawedziLeft;
	bool naKrawedziRight;

	float xPrzesuniecie;
	float yPrzesuniecie;

	Player();

	//Obiekt getObject();
	void sterowanie();
};

#endif