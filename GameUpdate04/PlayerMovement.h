#pragma once
#include<vector>
#include<iostream>
#include<SFML/Graphics.hpp>
class PlayerMovement
{
private :
	std::vector<std::string> idleName{ "idle1.png", "idle2.png", "idle3.png", "idle4.png" };
	sf::Texture idleTexture;
	sf::Texture flyTexture;
	sf::Sprite idleSprite;
	sf::Sprite flySprite;
	sf::Sprite playerMovementSprite;
	int countForward;
	int countBackward;
	int countUpward;
	int countDownward;
	int indexIdle;
	std::string mode;
	char keyPressed;
	sf::Vector2f playerPosition{ 400,400 };

public :
	PlayerMovement();
	void resetValue();
	void updateMoveMode(char key);
	void setMoveMode(char key);
	void updatePlayerMovement(sf::Vector2f playerPos);
	sf::Sprite getPlayerSprite();
	
};

