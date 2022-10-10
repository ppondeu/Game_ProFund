#pragma once
#include<vector>
#include<iostream>
#include<SFML/Graphics.hpp>
#define amtFilename 4
class Item
{
private :
	std::vector<std::string> fileName{ "healing.png", "lightning.png", "rage.png", "slowing.png" };
	sf::Texture itTexture;
	sf::RectangleShape itRect;
	sf::Vector2f itRandPos;
public :
	Item();
	sf::Vector2f ItemRandPos();
	sf::RectangleShape getRect();
	void itemUpdate();
};

