#include "Background.h"
Background::Background(std::string fileName) {
	bgTexture.loadFromFile(fileName);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(1, 1.1);
}
sf::Sprite Background::getSprite() {
	return bgSprite;
}