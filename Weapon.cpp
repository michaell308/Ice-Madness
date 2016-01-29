#include "Weapon.h"

Weapon::Weapon() {

}

Weapon::Weapon(sf::Texture bulletTexture, sf::Texture & weaponTextureR, sf::Texture & weaponTextureL, sf::SoundBuffer harpoonBuffer, sf::RenderWindow * theWindow) :
	hBuffer(harpoonBuffer),window(theWindow),bulletTextureW(bulletTexture) {
	wepSpriteR = sf::Sprite(weaponTextureR);
	wepSpriteR.setOrigin(wepSpriteR.getLocalBounds().width / 2.0f - 5, wepSpriteR.getLocalBounds().top); //set origin at middle x, bottom y so it rotates around this axis

	wepSpriteL = sf::Sprite(weaponTextureL);
	wepSpriteL.setOrigin(wepSpriteL.getLocalBounds().width / 2.0f + 5, wepSpriteL.getLocalBounds().top); //set origin at middle x, bottom y so it rotates around this axis

	wepSprite = wepSpriteR; //match character by starting weapon facing right
	bullets = std::vector<Bullet *>(0);
}

Weapon::Weapon(Weapon const & myWeapon) {
	copy(myWeapon);
}

void Weapon::copy(Weapon const & myWeapon) {
	clock = myWeapon.clock;
	wepSprite = myWeapon.wepSprite;
	bulletTextureW = myWeapon.bulletTextureW;
	wepSpriteR = myWeapon.wepSpriteR;
	wepSpriteL = myWeapon.wepSpriteL;
	sound = myWeapon.sound;
	hBuffer = myWeapon.hBuffer;
	window = myWeapon.window;
	for (int i = 0; i < myWeapon.bullets.size(); i++) {
		Bullet * myBullet = new Bullet();
		myBullet->mousePos = myWeapon.bullets[i]->mousePos;
		myBullet->startPos = myWeapon.bullets[i]->startPos;
		myBullet->bulletSprite = myWeapon.bullets[i]->bulletSprite;
		bullets.insert(bullets.begin(), myBullet);
	}
}

Weapon::~Weapon() {
	clear();
}

void Weapon::clear() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i] != NULL) {
			delete bullets[i];
			bullets[i] = NULL;
		}
	}
	bullets.clear();
}

Weapon const & Weapon::operator=(Weapon const & other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

void Weapon::setPos(sf::Sprite charSprite) {
	if (charSprite.getOrigin().x == 0) { //check for offset to adjust for animation
		wepSprite.setPosition(charSprite.getGlobalBounds().left + 23, charSprite.getGlobalBounds().top + 40);
	}
	else {
		wepSprite.setPosition(charSprite.getGlobalBounds().left + 35, charSprite.getGlobalBounds().top + 40);

	}
	sf::Vector2f curPos = wepSprite.getPosition();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

	const float PI = 3.14159265f;

	float dx = mousePosition.x - curPos.x;
	float dy = mousePosition.y - curPos.y;

	float rotation = (atan2(dy, dx)) * (180 / PI) - 90; //rotation angle in degrees

	wepSpriteL.setRotation(rotation);
	wepSpriteR.setRotation(rotation);
}

bool Weapon::getSide() {
	if (wepSprite.getRotation() >= 0 && wepSprite.getRotation() <= 180) {
		return true;
	}
	else {
		return false;
	}
}

void Weapon::setSide() {
	if (wepSprite.getRotation() >= 0 && wepSprite.getRotation() <= 180) {
		wepSprite = wepSpriteL;
	}
	else {
		wepSprite = wepSpriteR;
	}
}


void Weapon::draw() {
	window->draw(wepSprite);
}

//--BULLET--

Weapon::Bullet::Bullet() {

}

Weapon::Bullet::Bullet(sf::Sprite weaponSprite, sf::RenderWindow * window, sf::Texture & bulletTextureB) {
	bulletSprite = sf::Sprite(bulletTextureB);
	bulletSprite.setOrigin(bulletSprite.getLocalBounds().width / 2.0f, weaponSprite.getLocalBounds().height / 2.0f);
	mousePos = sf::Mouse::getPosition(*window);
}

void Weapon::drawB() {
	int screenX = window->getSize().x;
	int screenY = window->getSize().y;
	float shootWaitTime = 0.3f; //reload time
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > shootWaitTime) { //create bullet if left mouse click and shootWaitTime went by (stops spam shooting)
		sound.setBuffer(hBuffer);
		sound.play();
		createBullet(window);
		clock.restart();
	}
	for (int i = 0; i < bullets.size(); i++) {
		//if bullet exists and on screen
		if (bullets[i] != NULL && ((bullets[i]->bulletSprite.getPosition().y + bullets[i]->bulletSprite.getLocalBounds().height) >= 0) && ((bullets[i]->bulletSprite.getPosition().y - bullets[i]->bulletSprite.getLocalBounds().height) <= screenY) && ((bullets[i]->bulletSprite.getPosition().x + bullets[i]->bulletSprite.getLocalBounds().width) >= 0) && ((bullets[i]->bulletSprite.getPosition().x - bullets[i]->bulletSprite.getLocalBounds().width) <= screenX)) { //when bullet exists and is on screen, draw+move bullet
			window->draw(bullets[i]->bulletSprite);
			moveBullet(bullets[i]);
		}
		else {
			delete bullets[i];
			bullets[i] = NULL;
			bullets.erase(bullets.begin() + i);	//remove NULL from vector
		}
	}
}

void Weapon::createBullet(sf::RenderWindow * window) {
	Bullet * aBullet = new Bullet(wepSprite, window, bulletTextureW);
	//set appropriate start position based on weapon side
	if (getSide()) {
		aBullet->startPos = wepSprite.getTransform().transformPoint(sf::Vector2f((wepSprite.getLocalBounds().left + wepSprite.getLocalBounds().width - 20) / 2, wepSprite.getLocalBounds().top + 45));
	}
	else {
		aBullet->startPos = wepSprite.getTransform().transformPoint(sf::Vector2f((wepSprite.getLocalBounds().left + wepSprite.getLocalBounds().width + 20) / 2, wepSprite.getLocalBounds().top + 45));
	}
	aBullet->bulletSprite.setPosition(aBullet->startPos);
	aBullet->bulletSprite.setRotation(wepSprite.getRotation());
	bullets.insert(bullets.begin(), aBullet);
}

void Weapon::moveBullet(Bullet * & theBullet) {
	float dx = theBullet->mousePos.x - theBullet->startPos.x;
	float dy = theBullet->mousePos.y - theBullet->startPos.y;

	float norm = sqrt(dx*dx+dy*dy);
	dx = 15*dx / norm;
	dy = 15*dy / norm;
	theBullet->bulletSprite.move(dx, dy);
}

std::vector<Weapon::Bullet*> Weapon::getBullets() {
	return bullets;
}


