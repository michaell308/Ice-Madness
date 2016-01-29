#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include "Weapon.h"
#include "Map.h"
#include "Start.h"

const int screenX = 800;
const int screenY = 800;


int main() {
	sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Ice Madness", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(30);

	//--TEXTURES--
	sf::Texture iceTexture;
	if (!iceTexture.loadFromFile("Images/IceBall1S2.png")) {
		return -1;
	}
	sf::Texture startTexture;
	if (!startTexture.loadFromFile("Images/Start.png")) {
		return -1;
	}
	sf::Texture woodTexture;
	if (!woodTexture.loadFromFile("Images/woodPlankS.png")) {
		return -1;
	}
	sf::Texture charTextureR;
	if (!charTextureR.loadFromFile("Images/characterR.png")) {
		return -1;
	}
	sf::Texture charTextureL;
	if (!charTextureL.loadFromFile("Images/characterL.png")) {
		return -1;
	}
	sf::Texture charTextureR2;
	if (!charTextureR2.loadFromFile("Images/characterR2.png")) {
		return -1;
	}
	sf::Texture charTextureL2;
	if (!charTextureL2.loadFromFile("Images/characterL2.png")) {
		return -1;
	}
	sf::Texture harpoonGunTextureR;
	if (!harpoonGunTextureR.loadFromFile("Images/harpoonR.png")) {
		return -1;
	}
	sf::Texture harpoonGunTextureL;
	if (!harpoonGunTextureL.loadFromFile("Images/harpoonL.png")) {
		return -1;
	}
	sf::Texture harpoonAmmoTexture;
	if (!harpoonAmmoTexture.loadFromFile("Images/harpoonAmmo.png")) {
		return -1;
	}
	sf::Texture restartTexture;
	if (!restartTexture.loadFromFile("Images/restart.png")) {
		return -1;
	}
	sf::Texture ropeTexture;
	if (!ropeTexture.loadFromFile("Images/fullRopeS.png")) {
		return -1;
	}
	sf::Texture ropeTextureL;
	if (!ropeTextureL.loadFromFile("Images/ropeLS.png")) {
		return -1;
	}
	sf::Texture ropeTextureR;
	if (!ropeTextureR.loadFromFile("Images/ropeRS.png")) {
		return -1;
	}
	sf::Texture sTexture0;
	if (!sTexture0.loadFromFile("Images/snow0000.png")) {
		return -1;
	}
	sf::Texture sTexture1;
	if (!sTexture1.loadFromFile("Images/snow0001.png")) {
		return -1;
	}
	sf::Texture sTexture2;
	if (!sTexture2.loadFromFile("Images/snow0002.png")) {
		return -1;
	}
	sf::Texture sTexture3;
	if (!sTexture3.loadFromFile("Images/snow0003.png")) {
		return -1;
	}
	sf::Texture sTexture4;
	if (!sTexture4.loadFromFile("Images/snow0004.png")) {
		return -1;
	}
	sf::Texture sTexture5;
	if (!sTexture5.loadFromFile("Images/snow0005.png")) {
		return -1;
	}
	sf::Texture sTexture6;
	if (!sTexture6.loadFromFile("Images/snow0006.png")) {
		return -1;
	}
	sf::Texture sTexture7;
	if (!sTexture7.loadFromFile("Images/snow0007.png")) {
		return -1;
	}
	sf::Texture sTexture8;
	if (!sTexture8.loadFromFile("Images/snow0008.png")) {
		return -1;
	}
	sf::Texture sTexture9;
	if (!sTexture9.loadFromFile("Images/snow0009.png")) {
		return -1;
	}
	sf::Texture sTexture10;
	if (!sTexture10.loadFromFile("Images/snow0010.png")) {
		return -1;
	}
	sf::Texture sTexture11;
	if (!sTexture11.loadFromFile("Images/snow0011.png")) {
		return -1;
	}
	sf::Texture sTexture12;
	if (!sTexture12.loadFromFile("Images/snow0012.png")) {
		return -1;
	}
	sf::Texture sTexture13;
	if (!sTexture13.loadFromFile("Images/snow0013.png")) {
		return -1;
	}
	sf::Texture sTexture14;
	if (!sTexture14.loadFromFile("Images/snow0014.png")) {
		return -1;
	}
	sf::Texture sTexture15;
	if (!sTexture15.loadFromFile("Images/snow0015.png")) {
		return -1;
	}
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Images/background.png")) {
		return -1;
	}
	sf::Texture cursorTexture;
	if (!cursorTexture.loadFromFile("Images/cursor.png")) {
		return -1;
	}

	//--FONT--
	sf::Font font;
	if (!font.loadFromFile("Lumberjack.otf")) {
		return -1;
	}

	//--SOUND--
	sf::SoundBuffer harpoonBuffer;
	if (!harpoonBuffer.loadFromFile("Sounds/harpoonSound.wav")) {
		return -1;
	}
	sf::SoundBuffer iceBuffer;
	if (!iceBuffer.loadFromFile("Sounds/iceBreak4.wav")) {
		return -1;
	}
	sf::SoundBuffer fallBuffer;
	if (!fallBuffer.loadFromFile("Sounds/fallDeath.wav")) {
		return -1;
	}
	sf::SoundBuffer deathBuffer;
	if (!deathBuffer.loadFromFile("Sounds/death.wav")) {
		return -1;
	}
	sf::SoundBuffer jumpBuffer;
	if (!jumpBuffer.loadFromFile("Sounds/jump.wav")) {
		return -1;
	}
	sf::SoundBuffer ouchBuffer;
	if (!ouchBuffer.loadFromFile("Sounds/ouch.wav")) {
		return -1;
	}
	sf::SoundBuffer incBreakBuffer;
	if (!incBreakBuffer.loadFromFile("Sounds/incBreak.wav")) {
		return -1;
	}
	sf::Music music;
	if (!music.openFromFile("Sounds/music.ogg")) {
		return -1;
	}
	music.play();

	//--OBJECTS--
	Map theMap(10, 5, &iceTexture, &woodTexture, restartTexture, sTexture0, sTexture1, sTexture2, sTexture3, sTexture4, sTexture5, sTexture6, sTexture7, sTexture8, sTexture9, sTexture10, sTexture11, sTexture12, sTexture13, sTexture14, sTexture15, font, iceBuffer, deathBuffer, ouchBuffer, &window);

	Character theCharacter(0.5f, 1, charTextureR, charTextureL, charTextureR2, charTextureL2, &theMap, fallBuffer, jumpBuffer, incBreakBuffer, &window);

	Weapon theWeapon(harpoonAmmoTexture, harpoonGunTextureR, harpoonGunTextureL, harpoonBuffer, &window);
	
	TitleScreen theTScreen(startTexture, font, &window);

	//--BG + ROPES--
	sf::Sprite bgSprite(backgroundTexture);

	sf::Sprite ropeSprite(ropeTexture);
	ropeSprite.setOrigin(ropeSprite.getGlobalBounds().width / 2, ropeSprite.getGlobalBounds().height / 2);
	ropeSprite.setPosition(window.getSize().x / 2, window.getSize().y - 18);

	sf::Sprite ropeSpriteL(ropeTextureL);
	ropeSpriteL.setOrigin(ropeSpriteL.getGlobalBounds().width / 2, ropeSpriteL.getGlobalBounds().height / 2);
	ropeSpriteL.setPosition(20, window.getSize().y - 70);

	sf::Sprite ropeSpriteR(ropeTextureR);
	ropeSpriteR.setOrigin(ropeSpriteR.getGlobalBounds().width / 2, ropeSpriteR.getGlobalBounds().height / 2);
	ropeSpriteR.setPosition(window.getSize().x - 20, window.getSize().y - 70);
	//--START + CURSOR--
	bool start = false;

	sf::Sprite cursorSprite(cursorTexture);
	cursorSprite.setOrigin(cursorSprite.getGlobalBounds().width / 2, cursorSprite.getGlobalBounds().height / 2);
	window.setMouseCursorVisible(false);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left && theTScreen.onButton()) { //start game
					start = true;
				}
				if (event.mouseButton.button == sf::Mouse::Left && theMap.onButton()) { //restart game

					theMap = Map(10, 5, &iceTexture, &woodTexture, restartTexture, sTexture0, sTexture1, sTexture2, sTexture3, sTexture4, sTexture5, sTexture6, sTexture7, sTexture8, sTexture9, sTexture10, sTexture11, sTexture12, sTexture13, sTexture14, sTexture15, font, iceBuffer, deathBuffer, ouchBuffer, &window);

					theCharacter = Character(0.5f, 1, charTextureR, charTextureL, charTextureR2, charTextureL2, &theMap, fallBuffer, jumpBuffer, incBreakBuffer, &window);

					theWeapon = Weapon(harpoonAmmoTexture, harpoonGunTextureR, harpoonGunTextureL, harpoonBuffer, &window);

					start = true;
				}
			}
		}
		cursorSprite.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
		window.clear();
		window.draw(bgSprite); //draw background
		theMap.drawSnow(); //draw snow
		if (!start) {
			theTScreen.draw(); //draw title screen
		}
		theMap.draw(); //draw falling objects and ground blocks
		theCharacter.draw(); //draw the character
		theWeapon.setPos(theCharacter.getSprite()); //set weapon position
		if (start && !theMap.gameOverB) {
			theWeapon.drawB(); //draw bullets
		}
		theWeapon.draw(); //draw the weapon
		if (start && !theMap.gameOverB) {
			theWeapon.setSide();
			theCharacter.detectCollisionCG();
			theCharacter.move(&theWeapon);
			theMap.detectCollisionFG();
			theMap.updateFO();
			theMap.detectCollisionFC(theCharacter.getShape());
			theMap.detectCollisionFB(theWeapon.getBullets());
		}
		theMap.drawLevel(); //draw level+score+lives
		window.draw(ropeSpriteL); //draw left rope
		window.draw(ropeSpriteR); //draw right rope
		window.draw(ropeSprite); //draw middle rope
		window.draw(cursorSprite); //draw cursor
		if (theMap.gameOverB) {
			theMap.gameOver();
		}
		window.display();
	}
	return 0;
}