#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Background
{
private:
	std::string backgroundName;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	Background();
	void backgroundDraw(sf::RenderWindow &window);
};