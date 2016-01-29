#include "Start.h"

TitleScreen::TitleScreen(sf::Texture & texture, sf::Font font, sf::RenderWindow * theWindow) :
	tsFont(font),window(theWindow) {

	tsSprite = sf::Sprite(texture);
	tsSprite.setOrigin(sf::Vector2f(tsSprite.getLocalBounds().width / 2, tsSprite.getLocalBounds().height / 2));
	tsSprite.setPosition(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));

	text.setFont(tsFont);
	text.setString("Instructions: \n Beware the ice balls! \n They can break the bridge or hurt you \n W/A/S/D to move \n Mouse to aim and shoot \n Don't sit in one spot too long!");
	text.setCharacterSize(25);
	text.setColor(sf::Color::Black);
	text.setPosition(30, window->getSize().y / 2 - 200);
}

void TitleScreen::draw() {
	window->draw(text);
	window->draw(tsSprite);
}

bool TitleScreen::onButton() {
	return tsSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window));
}