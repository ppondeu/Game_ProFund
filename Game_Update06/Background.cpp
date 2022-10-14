#include "Background.h"

Background::Background() {
	backgroundName = "sprite/background.png";
	backgroundTexture.loadFromFile(backgroundName);
	backgroundSprite.setTexture(backgroundTexture);
}

void Background::backgroundDraw(sf::RenderWindow &window) {
	window.draw(backgroundSprite);
}