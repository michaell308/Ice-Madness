#include "Map.h"

Map::Map() {

}

Map::Map(int startNumFO, int startNumGB, sf::Texture * iceTexture, sf::Texture * woodTexture, sf::Texture & restartTexture, sf::Texture sTexture0, sf::Texture & sTexture1, sf::Texture & sTexture2, sf::Texture & sTexture3, sf::Texture & sTexture4, sf::Texture & sTexture5, sf::Texture & sTexture6, sf::Texture & sTexture7, sf::Texture & sTexture8, sf::Texture & sTexture9, sf::Texture & sTexture10, sf::Texture & sTexture11, sf::Texture & sTexture12, sf::Texture & sTexture13, sf::Texture & sTexture14, sf::Texture & sTexture15, sf::Font font, sf::SoundBuffer iceBuffer, sf::SoundBuffer deathBuffer, sf::SoundBuffer ouchBuffer, sf::RenderWindow * theWindow) :
	iceTextureM(iceTexture),woodTextureM(woodTexture),sText0(sTexture0),sText1(sTexture1),sText2(sTexture2),sText3(sTexture3),
	sText4(sTexture4),sText5(sTexture5),sText6(sTexture6),sText7(sTexture7),sText8(sTexture8),sText9(sTexture9),sText10(sTexture10),
	sText11(sTexture11),sText12(sTexture12),sText13(sTexture13),sText14(sTexture14),sText15(sTexture15),iBuffer(iceBuffer),dBuffer(deathBuffer),
	oBuffer(ouchBuffer),window(theWindow){

	foVector = std::vector<FallingObject*>(0);
	curNumFO = startNumFO; 
	maxNumFO = startNumFO;
	curNumGB = startNumGB;
	mapFont = font;
	restartButton = sf::Sprite(restartTexture);
	
	snowSprite = sf::Sprite(sText1);

	foCreate();
}

void Map::foCreate() {
	srand(time(NULL));
	for (int i = 0; i < maxNumFO; i++) { //initalize falling objects
		FallingObject * myFO = new FallingObject(*iceTextureM);
		resetPosition(myFO);
		float randVelY = (rand() % 2)* 0.02f;
		myFO->velY = maxVelY + randVelY;
		myFO->intersected = false;
		foVector.insert(foVector.begin(),myFO);
	}
	int initx = 20;
	int x = initx;
	for (int i = 0; i < curNumGB; i++) { //initalize ground blocks
		GroundBlock * myGB = new GroundBlock(*woodTextureM);
		myGB->gbSprite.setPosition(sf::Vector2f(x, window->getSize().y-myGB->gbSprite.getGlobalBounds().height));
		x += (((window->getSize().x - 2 * initx) - (curNumGB * myGB->gbSprite.getGlobalBounds().width)) / (curNumGB - 1)) + myGB->gbSprite.getGlobalBounds().width;
		gbVector.insert(gbVector.begin(), myGB);
	}
}

Map::Map(Map const & myMap) {
	copy(myMap);
}

void Map::copy(Map const & myMap) {
	gameOverB = myMap.gameOverB;
	for (int i = 0; i < myMap.foVector.size(); i++) {
		FallingObject * myFO = new FallingObject();
		myFO->foSprite = myMap.foVector[i]->foSprite;
		myFO->foCircle = myMap.foVector[i]->foCircle;
		myFO->velY = myMap.foVector[i]->velY;
		myFO->intersected = myMap.foVector[i]->intersected;
		foVector.insert(foVector.begin(), myFO);
	}
	for (int i = 0; i < myMap.gbVector.size(); i++) {
		GroundBlock * myGB = new GroundBlock();
		myGB->gbSprite = myMap.gbVector[i]->gbSprite;
		gbVector.insert(gbVector.begin(), myGB);
	}
	curNumFO = myMap.curNumFO;
	maxNumFO = myMap.maxNumFO;
	maxVelY = myMap.maxVelY;
	curNumGB = myMap.curNumGB;
	iceTextureM = myMap.iceTextureM;
	woodTextureM = myMap.woodTextureM;
	restartButton = myMap.restartButton;
	mapFont = myMap.mapFont;
	level = myMap.level;
	lives = myMap.lives;
	score = myMap.score;
	clock = myMap.clock;
	iBuffer = myMap.iBuffer;
	dBuffer = myMap.dBuffer;
	oBuffer = myMap.oBuffer;
	sound = myMap.sound;
	window = myMap.window;
	sText0 = myMap.sText0;
	sText1 = myMap.sText1;
	sText2 = myMap.sText2;
	sText3 = myMap.sText3;
	sText4 = myMap.sText4;
	sText5 = myMap.sText5;
	sText6 = myMap.sText6;
	sText7 = myMap.sText7;
	sText8 = myMap.sText8;
	sText9 = myMap.sText9;
	sText10 = myMap.sText10;
	sText11 = myMap.sText11;
	sText12 = myMap.sText12;
	sText13 = myMap.sText13;
	sText14 = myMap.sText14;
	sText15 = myMap.sText15;
	snowSprite = myMap.snowSprite;
	snowFrame = myMap.snowFrame;
}

Map::~Map() {
	clear();
}
void Map::clear() {
	for (int i = 0; i < foVector.size(); i++) {
		if (foVector[i] != NULL) {
			delete foVector[i];
			foVector[i] = NULL;
		}
	}
	foVector.clear();

	for (int i = 0; i < gbVector.size(); i++) {
		if (gbVector[i] != NULL) {
			delete gbVector[i];
			gbVector[i] = NULL;
		}
	}
	gbVector.clear();
}

Map const & Map::operator=(Map const & other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

void Map::updateFO() {
	for (int i = 0; i < foVector.size(); i++) {
		//if falling object off screen
		if (foVector[i]->foSprite.getPosition().y - foVector[i]->foSprite.getGlobalBounds().height / 2 > window->getSize().y) {
			resetPosition(foVector[i]);
			curNumFO--;
			//check if all falling objects have been destroyed
			if (curNumFO == 0) {
				nextLevel();
			}
		}
		else {
			foVector[i]->foSprite.setRotation(foVector[i]->foSprite.getRotation() + foVector[i]->randomNum);
			foVector[i]->foSprite.move(0, 15*foVector[i]->velY);
			foVector[i]->foCircle.move(0, 15*foVector[i]->velY);
		}
	}
}

void Map::resetPosition(FallingObject * myFO) {
	myFO->velY = 0.0f;
	int x = (rand() % (window->getSize().x - (int)myFO->foSprite.getGlobalBounds().width)) + myFO->foSprite.getGlobalBounds().width / 2;  //random x within bounds of map
	int y = (rand() % (window->getSize().y - (int)myFO->foSprite.getGlobalBounds().height)) - window->getSize().y; //random y above map, ready to fall
	myFO->foSprite.setPosition(sf::Vector2f(x, y));
	myFO->foCircle.setPosition(sf::Vector2f(x, y));
}

void Map::nextLevel() {
	level++;
	maxNumFO += 5; //x number more falling objects each level
	curNumFO = maxNumFO;
	maxVelY += 0.02f; //general speed increase of falling objects
	//make and add extra falling objects to vector for next level
	for (int i = foVector.size(); i < maxNumFO; i++) {
		FallingObject * myFO = new FallingObject(*iceTextureM);
		resetPosition(myFO);
		foVector.insert(foVector.begin(), myFO);
	}
	for (int i = 0; i < foVector.size(); i++) {
		float randVelY = (rand() % 2)* 0.03f; //give falling objects random speed within range
		//update all velY to start next level
		foVector[i]->velY = maxVelY + randVelY;
		foVector[i]->intersected = false;
	}
}

void Map::detectCollisionFG() {
	for (int i = 0; i < gbVector.size(); i++) {
		for (int j = 0; j < foVector.size(); j++) {
			if (!foVector[j]->intersected && intersects(foVector[j], gbVector[i]->gbSprite.getGlobalBounds(), 1)) { //collision detected
				sound.setBuffer(iBuffer);
				sound.play();
				gbVector.erase(gbVector.begin() + i);
				curNumFO--;
				foVector[j]->intersected = true;
				resetPosition(foVector[j]);
				if (curNumFO == 0) {
					nextLevel();
				}
				break;
			}
		}
	}
}

void Map::detectCollisionFC(sf::RectangleShape charShape) {
	for (int i = 0; i < foVector.size(); i++) {
		if (!foVector[i]->intersected && intersects(foVector[i], charShape.getGlobalBounds(), 0)) { 			
			foVector[i]->intersected = true;
			lives--;
			if (lives <= 0) {
				sound.setBuffer(dBuffer);
				sound.play();
				gameOverB = true;
			}
			else {
				sound.setBuffer(oBuffer);
				sound.play();
			}
			resetPosition(foVector[i]);
			curNumFO--;
			if (curNumFO == 0) {
				nextLevel();
			}
		}
	}
}

void Map::detectCollisionFB(std::vector<Weapon::Bullet*> bullets) {
	for (int i = 0; i < bullets.size(); i++) {
		for (int j = 0; j < foVector.size(); j++) {
			if (!foVector[j]->intersected && intersects(foVector[j], bullets[i]->bulletSprite.getGlobalBounds(), 0)) { //collision detected
				sound.setBuffer(iBuffer);
				sound.play();
				bullets.erase(bullets.begin() + i);
				score += 10;
				curNumFO--;
				foVector[j]->intersected = true;
				resetPosition(foVector[j]);
				if (curNumFO == 0) {
					nextLevel();
				}
				break;
			}
		}
	}
}

bool Map::intersects(FallingObject * fo, sf::FloatRect myRect, bool FG) {
	if (fo->foCircle.getPosition().y < 550 && FG) {
		return false;
	}

	float circleX = fo->foCircle.getPosition().x;
	float closestX;
	if (circleX < myRect.left) { //circle to left of rect
		closestX = myRect.left;
	}
	else if (circleX > myRect.left + myRect.width) { //circle to right of rect
		closestX = myRect.left + myRect.width;
	}
	else {
		closestX = circleX;
	}

	float circleY = fo->foCircle.getPosition().y;
	float closestY;
	if (circleY < myRect.top) { //circle above rect
		closestY = myRect.top;
	}
	else if (circleY > myRect.top + myRect.height) { //circle below rect
		closestY = myRect.top + myRect.height;
	}
	else {
		closestY = circleY;
	}

	float dx = abs(circleX - closestX) * abs(circleX - closestX);
	float dy = abs(circleY - closestY) * abs(circleY - closestY);
	return sqrt(dx + dy) < fo->foCircle.getRadius();
}

void Map::gameOver() {
	sf::RectangleShape backdrop((sf::Vector2f)window->getSize());
	backdrop.setFillColor(sf::Color(100, 0, 0, 150));
	window->draw(backdrop);
	sf::Text text;
	text.setFont(mapFont);
	text.setCharacterSize(50);
	text.setString("Game Over!");
	text.setColor(sf::Color::Black);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(window->getSize().x / 2, window->getSize().y / 2);
	window->draw(text);
	restartButton.setOrigin(restartButton.getGlobalBounds().width / 2, restartButton.getGlobalBounds().height / 2);
	restartButton.setPosition(window->getSize().x / 2, window->getSize().y / 2 + text.getGlobalBounds().width);
	window->draw(restartButton);
}

bool Map::onButton() {
	return restartButton.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window));
}

int Map::getGBHeight() {
	if (gbVector.size() == 0) {
		return 0;
	}
	return gbVector[0]->gbSprite.getGlobalBounds().height;
}

void Map::deleteGB(int i) {
	if (i < gbVector.size()) {
		gbVector.erase(gbVector.begin() + i);
	}
}

void Map::draw() {
	for (int i = 0; i < foVector.size(); i++) {
		window->draw(foVector[i]->foSprite);
	}
	for (int i = 0; i < gbVector.size(); i++) {
		window->draw(gbVector[i]->gbSprite);
	}
}

void Map::drawLevel() {
	sf::Text text;
	text.setFont(mapFont);
	text.setString("Level: " + std::to_string(level));
	text.setCharacterSize(25);
	text.setColor(sf::Color::Black);
	text.setPosition(5, 0);
	window->draw(text);

	sf::Text text3;
	text3.setFont(mapFont);
	text3.setString("Score: " + std::to_string(score));
	text3.setCharacterSize(25);
	text3.setColor(sf::Color::Black);
	text3.setPosition(window->getSize().x - text3.getGlobalBounds().width - 5, 0);
	window->draw(text3);

	sf::Text text2;
	text2.setFont(mapFont);
	text2.setString("Life: " + std::to_string(lives));
	text2.setCharacterSize(25);
	text2.setColor(sf::Color::Black);
	text2.setPosition(text3.getPosition().x, text3.getPosition().y + text2.getGlobalBounds().height + 5);
	window->draw(text2);
}

void Map::drawSnow() {
	if (clock.getElapsedTime().asSeconds() > 0.3f) {
		snowFrame++;
		if (snowFrame == 0) {
			snowSprite.setTexture(sText0);
		}
		else if (snowFrame == 1) {
			snowSprite.setTexture(sText1);
		}
		else if (snowFrame == 2) {
			snowSprite.setTexture(sText2);
		}
		else if (snowFrame == 3) {
			snowSprite.setTexture(sText3);
		}
		else if (snowFrame == 4) {
			snowSprite.setTexture(sText4);
		}
		else if (snowFrame == 5) {
			snowSprite.setTexture(sText5);
		}
		else if (snowFrame == 6) {
			snowSprite.setTexture(sText6);
		}
		else if (snowFrame == 7) {
			snowSprite.setTexture(sText7);
		}
		else if (snowFrame == 8) {
			snowSprite.setTexture(sText8);
		}
		else if (snowFrame == 9) {
			snowSprite.setTexture(sText9);
		}
		else if (snowFrame == 10) {
			snowSprite.setTexture(sText10);
		}
		else if (snowFrame == 11) {
			snowSprite.setTexture(sText11);
		}
		else if (snowFrame == 12) {
			snowSprite.setTexture(sText12);
		}
		else if (snowFrame == 13) {
			snowSprite.setTexture(sText13);
		}
		else if (snowFrame == 14) {
			snowSprite.setTexture(sText14);
		}
		else {
			snowSprite.setTexture(sText15);
			snowFrame = -1;
		}
		clock.restart();
	}
	snowSprite.setOrigin(snowSprite.getGlobalBounds().width / 2, snowSprite.getGlobalBounds().height / 2);
	snowSprite.setPosition(window->getSize().x/2, window->getSize().y/2);
	window->draw(snowSprite);
}

std::vector<Map::GroundBlock*> Map::getGBVector() {
	return gbVector;
}

Map::FallingObject::FallingObject() {
	randomNum = 1 * ((rand() % 3 + 1)*0.5f);
}

Map::FallingObject::FallingObject(sf::Texture & iceTextureFO) {
	velY = 0.0f;
	foSprite = sf::Sprite(iceTextureFO);
	foSprite.setOrigin(foSprite.getGlobalBounds().width / 2, foSprite.getGlobalBounds().height / 2);
	foCircle = sf::CircleShape(10.0f);
	foCircle.setOrigin(foCircle.getRadius(), foCircle.getRadius());
	randomNum = 5 * ((rand() % 3 + 1)*0.5f);

}

Map::GroundBlock::GroundBlock() {

}

Map::GroundBlock::GroundBlock(sf::Texture & woodTextureGB) {
	gbSprite = sf::Sprite(woodTextureGB);
}