#include "Item.h"
Item::Item() {
	itemUpdate();
}
sf::Vector2f Item::ItemRandPos() {
	itRandPos.x = static_cast<float>(rand() % 760);
	itRandPos.y = static_cast<float>(rand() % 780 + 150);
	return itRandPos;
}
sf::RectangleShape Item::getRect() {
	return itRect;
}

void Item::itemUpdate() {
	itRandPos = ItemRandPos();
	int randIDX = rand() % amtFilename;
	itTexture.loadFromFile(fileName[randIDX]);
	itRect.setTexture(&itTexture);
	itRect.setPosition(itRandPos);
	itRect.setSize(sf::Vector2f(100, 100));
}
