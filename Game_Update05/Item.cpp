#include "Item.h"

Item::Item() {

	itemName = "sprite/item.png";
	itemTexture.loadFromFile(itemName);
	itemSprite.setTexture(itemTexture);
	itemSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	maxItem = 4;
	itemSize = sf::Vector2i(itemTexture.getSize().x / maxItem, itemTexture.getSize().y);
	updateTexture();

}

void Item::updateTexture() {

	randomIndexItem = rand() % maxItem;
	imagePosition = sf::Vector2i(static_cast<int>(itemSize.x * randomIndexItem), 0);
	itemPosition = sf::Vector2f{ static_cast<float>(rand() % 960), static_cast<float>(rand() % 900) };
	itemIntRect = sf::IntRect{ imagePosition, itemSize };
	itemSprite.setTextureRect(itemIntRect);
	itemSprite.setPosition(itemPosition);

}
void Item::itemRender(float deltaTime) {

	totalTime += deltaTime;
	if (totalTime >= itemTime) {
		updateTexture();
		totalTime -= itemTime;
	}

}
void Item::itemDraw(sf::RenderWindow &window) {

	window.draw(itemSprite);

}