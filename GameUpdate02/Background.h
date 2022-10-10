#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
class Background
{
private :
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
public :
	Background(std::string fileName = "bgDragonball.png");
	sf::Sprite getSprite();
};




