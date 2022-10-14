#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class Player
{
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::IntRect playerSize;
	sf::Vector2f move{0.0f,0.0f};
	sf::Vector2f playerPosition;
	sf::Vector2f playerScale{4,4};


	int amountFrame = 4;

	float switchTime = 0.19f;
	float switchTime2 = 0.1f;

	std::string side = "right";
	std::string mode = "idle";
	std::string fileName = "Sprite/player_idle_rs.png";

	bool attackState = false;
	float totalTime = 0.0f;
	float totalTime2 = 0.0f;
	int currentRun = 0;
	int movedRun = 0;
	int attackedRun = 0;
	int indexFrame = 0;

	void updateValue(std::string mode, std::string side, float x, std::string fileName, int amountFrame);
	void setPlayerSize();
	void setTextureSprite();

public:
	
	Player();
	void playerRender(float deltaTime);
	void playerDraw(sf::RenderWindow& window);
};

