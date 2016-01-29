//#pragma once

#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Weapon{
public:
	struct Bullet {
		//default bullet constructor
		Bullet();
		//constructor
		Bullet(sf::Sprite weaponSprite, sf::RenderWindow * window, sf::Texture & bulletTextureB);
		//mouse position when bullet is created
		sf::Vector2i mousePos;
		//start position based on weapon position
		sf::Vector2f startPos;
		sf::Sprite bulletSprite;
	};
	//default constructor
	Weapon();
	//constructor
	Weapon(sf::Texture bulletTexture, sf::Texture & weaponTextureR, sf::Texture & weaponTextureL, sf::SoundBuffer harpoonBuffer, sf::RenderWindow * theWindow);
	//copy constructor
	Weapon(Weapon const & myWeapon);
	//destructor
	~Weapon();
	//operator=
	Weapon const & operator=(Weapon const & other);
	//set position of weapon (including rotation towards mouse)
	void setPos(sf::Sprite charSprite);
	//get weapon side based on rotation (false is right and true is left)
	bool getSide(); //used for animation in Character.h
	//set weapon sprite based on rotation
	void setSide();
	//draw weapon
	void draw();
	//draw and move bullets
	void drawB();

	std::vector<Bullet*> getBullets(); //used for collision detection in Map.h
private:

	void copy(Weapon const & myWeapon); //helper for copy constructor and operator=
	void clear(); //helper for destructor and operator=

	sf::Sprite wepSprite;
	sf::Sprite wepSpriteR;
	sf::Sprite wepSpriteL;

	sf::Sound sound;
	sf::SoundBuffer hBuffer;

	sf::RenderWindow * window;

	//--BULLET--
	//creates bullet using bulletTextureW
	void createBullet(sf::RenderWindow * window);
	//moves bullet towards mouse
	void moveBullet(Bullet * & theBullet);

	std::vector<Bullet*> bullets; //holds all existing bullets
	sf::Texture bulletTextureW; //used for creating bullet
	sf::Clock clock; //used for bullet shooting


};

#endif