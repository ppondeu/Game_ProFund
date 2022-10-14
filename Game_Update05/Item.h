#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>


class Item
{
private:

	std::string itemName;
	sf::Texture itemTexture;
	sf::Sprite itemSprite;
	unsigned maxItem;
	unsigned randomIndexItem;
	sf::Vector2i itemSize;
	sf::Vector2i imagePosition;
	sf::IntRect itemIntRect;
	sf::Vector2f itemPosition;
	float totalTime = 0.0f;
	float itemTime = 3.0f;

	void updateTexture();
public:

	Item();
	void itemRender(float deltaTime);
	void itemDraw(sf::RenderWindow& window);

};

