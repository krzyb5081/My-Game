#pragma once

#include <SFML/Graphics.hpp>

class Obiekt {

public:

	sf::Texture * texture;
	sf::Sprite * sprite;
	float * predkosc;
	int * warstwa;
	bool * isVisible;
	float * startX;
	float * startY;
	float * height;
	float * width;


    void load(const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa);
	void copy(Obiekt &obiekt);
	void move(float x, float y);
	void setScale(float scaleX, float scaleY);
	
    



};
