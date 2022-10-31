#include "Background.h"

Background::Background(std::string stringName) {
	this->stringName = stringName;
	backgroundTexture.loadFromFile(stringName);
	backgroundSprite.setTexture(backgroundTexture);
	
}

void Background::backgroundDraw(sf::RenderWindow& window) {
	window.draw(backgroundSprite);
}
