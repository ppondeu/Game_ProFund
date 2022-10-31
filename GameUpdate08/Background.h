#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class Background
{
private:
	sf::String stringName;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
public:
	Background(std::string stringName);
	void backgroundDraw(sf::RenderWindow& window);
};



