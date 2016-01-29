#include "Character.h"

Character::Character() {

}

Character::Character(float velocity, float acceleration, sf::Texture & textureR, sf::Texture & textureL, sf::Texture & textureR2, sf::Texture & textureL2, Map * theMap, sf::SoundBuffer fallDeathBuffer, sf::SoundBuffer jumpBuffer, sf::SoundBuffer incBreakBuffer, sf::RenderWindow * theWindow):
	charMap(theMap),fdBuffer(fallDeathBuffer),jBuffer(jumpBuffer),ibBuffer(incBreakBuffer),window(theWindow) {

	vel = velocity;
	accl = acceleration;
	windowYmGBH = window->getSize().y - charMap->getGBHeight();

	charSpriteR = sf::Sprite(textureR);
	charSpriteR2 = sf::Sprite(textureR2);
	charSpriteL = sf::Sprite(textureL);
	charSpriteL2 = sf::Sprite(textureL2);

	sf::Vector2f startPos(window->getSize().x / 2 - charSpriteR.getGlobalBounds().width / 2, windowYmGBH - charSpriteR.getGlobalBounds().height); //window->getSize().y - charSpriteR.getGlobalBounds().height - charMap->getGBHeight());

	charSpriteR.setPosition(startPos);
	charSpriteL.setPosition(startPos);
	charSpriteL2.setOrigin(12, 0); //offset to fix animations

	charSprite = charSpriteR; //initally faces right
	
	charShape = sf::RectangleShape(sf::Vector2f(charSprite.getGlobalBounds().width-18,charSprite.getGlobalBounds().height));
	charShape.setOrigin(charShape.getGlobalBounds().width / 2, charShape.getGlobalBounds().height / 2);
	charShape.setPosition(charSprite.getPosition().x+charSprite.getGlobalBounds().width/2,charSprite.getPosition().y+charSprite.getGlobalBounds().height/2);
}

void Character::move(Weapon * theWep) {
	int screenX = window->getSize().x;
	int screenY = window->getSize().y;
	//Left+Right Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //stop if both keys pressed
		goX = 0.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && charShape.getPosition().x - charShape.getGlobalBounds().width/2 > 0 && !botL) { //left if A and in bounds and not on ground block edge
		//goX = -0.5f;
		goX = -10.0f;
		botR = false;
		animation(theWep);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && charShape.getPosition().x + charShape.getGlobalBounds().width/2 < screenX && !botR) { //right 
		//goX = 0.5f;
		goX = 10.0f;
		botL = false;
		animation(theWep);
	}
	else { //stop if no keys pressed
		goX = 0.0f;
		//flip sprite left or right
		if (theWep->getSide()) {
			charSprite = charSpriteL;
		}
		else {
			charSprite = charSpriteR;
		}
	}
	//Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && cgIntersect && charShape.getGlobalBounds().top + charShape.getGlobalBounds().height <= windowYmGBH + 5) { //jump if W and on ground block and above ground block
		vel = -15.0f;
		jumping = true;
		cgIntersect = false;
		onBlockB = false;
		sound.setBuffer(jBuffer);
		sound.play();
		gbSprite->setColor(sf::Color(255, 255, 255, 255)); //reset color to original
	}
	//Gravity
	if (charShape.getPosition().y + charShape.getGlobalBounds().height / 2 <= screenY+charSprite.getGlobalBounds().height + 100 || jumping) { //!onGround or jumping 
		vel = vel + accl;
		goY = vel;
	}
	else { //onGround && !jumping
		goY = 0.0f;
	}
	jumping = false;
	if (charSprite.getGlobalBounds().top + charSprite.getGlobalBounds().height >= screenY + charSprite.getGlobalBounds().height + 100) { //player off screen (game over)
		sound.setBuffer(fdBuffer);
		sound.play();
		charMap->gameOverB = true;
	}
	charSpriteL.move(goX, goY);
	charSpriteR.move(goX, goY);
	charSprite.move(goX, goY);
	charShape.move(goX, goY);
}

void Character::detectCollisionCG() {
	std::vector<Map::GroundBlock*> gbVector = charMap->getGBVector();
	for (int i = 0; i < gbVector.size(); i++) {
		sf::FloatRect myRect = gbVector[i]->gbSprite.getGlobalBounds();
		myRect.height = 5.0f;
		//if upper part of ground block contains bottom left or bottom right of character shape
		if (myRect.contains(sf::Vector2f(charShape.getGlobalBounds().left, charShape.getGlobalBounds().top + charShape.getGlobalBounds().height)) || myRect.contains(sf::Vector2f(charShape.getGlobalBounds().left + charShape.getGlobalBounds().width, charShape.getGlobalBounds().top + charShape.getGlobalBounds().height))) {
			cgIntersect = true;
			vel = -accl;
			if (!onBlockB) {
				onBlockB = true;
				gbSprite = &gbVector[i]->gbSprite;
				clock2.restart();
			}
			onBlock(i);
		}
		sf::FloatRect myOtherRect = gbVector[i]->gbSprite.getGlobalBounds();
		myOtherRect.top += myRect.height;
		//if lower part of ground block contains bottom left
		if (myOtherRect.contains(sf::Vector2f(charShape.getGlobalBounds().left, charShape.getGlobalBounds().top + charShape.getGlobalBounds().height))) {
			botL = true;
		}
		//bottom right
		if (myOtherRect.contains(sf::Vector2f(charShape.getGlobalBounds().left + charShape.getGlobalBounds().width, charShape.getGlobalBounds().top + charShape.getGlobalBounds().height))) {
			botR = true;
		}
	}
}

void Character::onBlock(int i) {
	if (clock2.getElapsedTime().asSeconds() >  4) {
		sound2.setBuffer(ibBuffer); 
		sound2.play();
		gbSprite->setColor(sf::Color(255, 50, 50, 200)); //alert player after 4 seconds by changing ground block color
	}
	if (clock2.getElapsedTime().asSeconds() >  5) {
		charMap->deleteGB(i);
	}
}

void Character::animation(Weapon * theWep) {
	if (clock.getElapsedTime().asSeconds() > 0.1f) {
		if (theWep->getSide()) { //facing left
			if (animMode) {
				charSpriteL2.setPosition(charSpriteL.getPosition());
				charSprite = charSpriteL2;
			}
			else {
				charSprite = charSpriteL;
			}
		}
		else { //facing right
			if (animMode) {
				charSpriteR2.setPosition(charSpriteR.getPosition());
				charSprite = charSpriteR2;
			}
			else {
				charSprite = charSpriteR;
			}
		}
		clock.restart();
		animMode = !animMode;
	}
}

void Character::draw() {
	window->draw(charSprite);
}

sf::RectangleShape Character::getShape() {
	return charShape;
}

sf::Sprite Character::getSprite() {
	return charSprite;
}