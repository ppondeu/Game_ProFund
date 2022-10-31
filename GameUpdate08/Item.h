#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>


class Item
{
private:

	std::string itemName;
	sf::Texture itemTexture;
	
	unsigned maxItem;
	
	sf::Vector2i itemSize;
	sf::Vector2i imagePosition;
	sf::IntRect itemIntRect;
	sf::Vector2f itemPosition;
	float totalTime = 0.0f;
	float itemTime = 10.0f;
	void updateTexture();
public:
	unsigned randomIndexItem;
	bool getItem = false;
	sf::Sprite itemSprite;
	sf::Image itemImage;
	Item();
	void setGetItem();
	void mouseButtonPressedState(sf::Vector2f mousePosition);
	void itemRender(float deltaTime);
	void itemDraw(sf::RenderWindow& window);

};


