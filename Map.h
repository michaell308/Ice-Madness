#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Weapon.h"

class Map {
public:
	struct FallingObject {
		//default constructor
		FallingObject();
		//constructor
		FallingObject(sf::Texture & iceTextureFO);

		sf::Sprite foSprite;
		sf::CircleShape foCircle; //hitbox
		float velY = 0.0f;
		bool intersected = false; //ensures intersects only once each level
		float randomNum = 0.0f; //random number to rotate by
	};

	struct GroundBlock {
		//default constructor
		GroundBlock();
		//constructor
		GroundBlock(sf::Texture & woodTextureGB);

		sf::Sprite gbSprite;
	};
	//default constructor
	Map();
	//constructor
	Map(int startNumFO, int startNumGB, sf::Texture * iceTexture, sf::Texture * woodTexture, sf::Texture & restartTexture, sf::Texture sTexture0, sf::Texture & sTexture1, sf::Texture & sTexture2, sf::Texture & sTexture3, sf::Texture & sTexture4, sf::Texture & sTexture5, sf::Texture & sTexture6, sf::Texture & sTexture7, sf::Texture & sTexture8, sf::Texture & sTexture9, sf::Texture & sTexture10, sf::Texture & sTexture11, sf::Texture & sTexture12, sf::Texture & sTexture13, sf::Texture & sTexture14, sf::Texture & sTexture15, sf::Font font, sf::SoundBuffer iceBuffer, sf::SoundBuffer deathBuffer, sf::SoundBuffer ouchBuffer, sf::RenderWindow * theWindow);
	//copy constructor
	Map(Map const & myMap);
	//destructor
	~Map();
	//operator=
	Map const & operator=(Map const & other);
	//moves (and rotates) falling objects and changes level when appropriate
	void updateFO();
	//sets up next level and starts it
	void nextLevel();
	//collisions between falling objects and ground blocks
	void detectCollisionFG();
	//collisions between falling objects and character
	void detectCollisionFC(sf::RectangleShape charShape);
	//collisions between falling objects and bullets
	void detectCollisionFB(std::vector<Weapon::Bullet*> bullets);
	//displays everything for game over
	void gameOver();
	//mouse on restart button (when game over)
	bool onButton();
	//gets height of a ground block
	int getGBHeight(); //used for setting inital position in Character.h
	//deletes ground block from vector at index i
	void deleteGB(int i);
	//draws falling objects and ground blocks
	void draw();
	//draws text for level, score, and life
	void drawLevel();
	//animates snow
	void drawSnow();

	std::vector<GroundBlock*> getGBVector(); //used for detectCollisionCG() in Character.h

	bool gameOverB = false; //used in WinMain.cpp to signal game over

private:
	void copy(Map const & myMap); //helper for copy constructor and operator=
	void clear(); //helper for destructor and operator=

	//helper method in map constructor (creates falling objects for level one)
	void foCreate(); 
	//reset position of a falling object
	void resetPosition(FallingObject * myFO);
	//checks intersection between falling object and rectangle (from player, ground block, or bullet). FG bool used for optimization with falling object/ground block collisions (0 not optimized, 1 optimized)
	bool intersects(FallingObject * fo, sf::FloatRect myRect, bool FG);

	std::vector<FallingObject*> foVector; //vector holding all falling objects
	std::vector <GroundBlock*> gbVector; //vector holding all ground blocks
	int curNumFO; //number of falling objects on screen currently
	int maxNumFO; //total number of falling objects for this level
	float maxVelY = 0.2f; //general velocity of all falling objects (within range)
	int curNumGB; //current number of ground blocks
	sf::Texture * iceTextureM; //holds texture for falling objects
	sf::Texture * woodTextureM; //holds texture for ground blocks

	sf::Sprite restartButton;
	sf::Font mapFont;

	int level = 1;
	int lives = 3;
	int score = 0;


	sf::SoundBuffer iBuffer;
	sf::SoundBuffer dBuffer;
	sf::SoundBuffer oBuffer;

	sf::Sound sound;

	sf::RenderWindow * window;


	//--SNOW--
	sf::Texture sText0;
	sf::Texture sText1;
	sf::Texture sText2;
	sf::Texture sText3;
	sf::Texture sText4;
	sf::Texture sText5;
	sf::Texture sText6;
	sf::Texture sText7;
	sf::Texture sText8;
	sf::Texture sText9;
	sf::Texture sText10;
	sf::Texture sText11;
	sf::Texture sText12;
	sf::Texture sText13;
	sf::Texture sText14;
	sf::Texture sText15;

	sf::Sprite snowSprite;

	sf::Clock clock; //used for snow animation
	int snowFrame = -1; //used for snow animation
};


#endif MAP_H