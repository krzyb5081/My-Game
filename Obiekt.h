#pragma once

#include <SFML/Graphics.hpp>

class Obiekt {

public:

	static const int INTERACTION_TYPE_NONE = 0;
	static const int INTERACTION_TYPE_WALL = 1;
	static const int INTERACTION_TYPE_GATEWAY = 2;
	static const int INTERACTION_TYPE_USABLE = 3;

	int * idNumber;

	sf::Texture * texture;
	sf::Sprite * sprite;
	float * predkosc;
	int * warstwa;
	bool * isVisible;
	bool * isBehindScene;
	float * startX;
	float * startY;
	float * height;
	float * width;
	int * interactionType;
	std::string * interactionData;//do kad prowadzi przejscie co robi E to use itd



    void load(int idNumber, const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa, int interactionType, std::string interactionData, bool isBehindScene);
	void copy(Obiekt &obiekt);
	void move(float x, float y);
	void setSpritePosition(float x, float y);
	void setScale(float scaleX, float scaleY);


};
