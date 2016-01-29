//#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"

class Character{
public:
	//default constructor
	Character();
	//constructor
	Character(float velocity, float acceleration, sf::Texture & textureR, sf::Texture & textureL, sf::Texture & textureR2, sf::Texture & textureL2, Map * theMap, sf::SoundBuffer fallDeathBuffer, sf::SoundBuffer jumpBuffer, sf::SoundBuffer incBreakBuffer, sf::RenderWindow * theWindow);
	//moves character (theWep used to check sides for animation)
	void move(Weapon * theWep);
	//detect collision between character and ground blocks
	void detectCollisionCG();
	//draw charSprite
	void draw();

	sf::RectangleShape getShape(); //used for detectCollisionFC in Map.h
	sf::Sprite getSprite(); //used for setPos in Weapon.h 

private:

	//set color and delete ground block at appropriate times
	void onBlock(int i);
	//walking animation for player
	void animation(Weapon * theWep);

	float vel;
	float accl;
	float goX = 0.0f;
	float goY = 0.0f;
	bool jumping = false;
	bool cgIntersect = false; //character+ground block intersect
	bool botL = false;
	bool botR = false;
	bool animMode = false; // false is right/left and true is right2/left2
	bool onBlockB = false;
	float windowYmGBH;

	sf::Clock clock;  //used for animation
	sf::Sprite charSprite;
	sf::Sprite charSpriteR;
	sf::Sprite charSpriteL;
	sf::Sprite charSpriteR2;
	sf::Sprite charSpriteL2;

	Map * charMap;

	sf::RectangleShape charShape; //used for hitbox

	sf::SoundBuffer fdBuffer;
	sf::SoundBuffer jBuffer;
	sf::SoundBuffer ibBuffer;

	sf::Sound sound;
	sf::Sound sound2;

	sf::Clock clock2; //used for destroying ground block
	sf::Sprite * gbSprite;

	sf::RenderWindow * window;
};

#endif