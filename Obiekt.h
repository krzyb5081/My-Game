#pragma once

#include <SFML/Graphics.hpp>

class Obiekt {

public:

	int * idNumber;

	sf::Texture * texture;
	sf::Sprite * sprite;
	std::string * textureName;
	
	int * warstwa;
	bool * isVisible;
	bool * isBehindScene;
	bool * isTransparent;

	float * predkosc;
	float * startX;
	float * startY;
	float * height;
	float * width;

	bool * colides;
	bool * interacts;
	std::string * interactionData;//do kad prowadzi przejscie co robi E to use itd
	bool * isFlat;



    void load(int idNumber, const char * nazwaTextury, float startX, float startY, float predkosc, int warstwa, bool colides, bool interacts, std::string interactionData, bool isFlat, bool isBehindScene);
	void copy(Obiekt &obiekt);
	void move(float x, float y);
	void setSpritePosition(float x, float y);
	void setScale(float scaleX, float scaleY);
	void makeObiectTransparent(bool isTransparent);


};
