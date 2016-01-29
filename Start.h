#ifndef START_H
#define START_H

#include <SFML/Graphics.hpp>

class TitleScreen {
public:
	//constructor
	TitleScreen(sf::Texture & texture, sf::Font font, sf::RenderWindow * theWindow);
	//draw tsSprite+text
	void draw();
	//check if mouse is on button
	bool onButton();

private:
	sf::Sprite tsSprite;
	sf::Font tsFont;
	sf::Text text;
	sf::RenderWindow * window;

};

#endif START_H

