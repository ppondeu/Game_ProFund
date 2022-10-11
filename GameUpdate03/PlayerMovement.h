#pragma once
#include<vector>
#include<iostream>
#include<SFML/Graphics.hpp>
class PlayerMovement
{
private :
	std::vector<std::string> playerMovementFilename{ "default1.png", "default2.png", "default3.png", "default4.png" };
	sf::Texture defaultTexture;
	sf::Texture flyTexture;
	sf::Sprite defaultSprite;
	sf::Sprite flySprite;
	std::string Mode;
public :
	PlayerMovement(std::string fileName);
	sf::Sprite getTempSprite();
	sf::Sprite tmpSprite;
	sf::Vector2f PlayerMovementPosition{465, 560};
	int indexDefault;
	void updateDefault();
	void updateFly(char KeyPressed);
	void updatePlayerPosition(std::string mode);
	sf::Sprite getDefaultSprite();
	sf::Sprite getFlySprite();
};

