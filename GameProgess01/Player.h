#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
class Player
{
private:
	std::string filename;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Vector2i imageSize;
	sf::Vector2i countImage{ 0,0 };
	sf::IntRect playerIntRect;
	std::vector<int> indexFrame;
	std::vector<int> maxFrame;
	int currentStance = 0;

	float totalTime = 0.0f;
	float totalTimeII = 0.0f;
	float frameTime = 0.19f;
	float moveTime = 0.1f;

	std::string key;
	std::string eventType;

	sf::Vector2f move{ 0,0 };

	std::string mode = "idle";
	std::string side = "right";

	bool isAttack = false;
	int countPressed = 0;
	bool countUltimateStance = 0;
	int countAttackStance = 0;
	int attackNo = 0;
	void setFrame();
	void resetStance();

public:
	Player(std::string filename, std::vector<int> &maxFrame);
	void setRowColumn(sf::Vector2i countImage);
	void playerEvent(std::string Event, std::string key);
	void playerRender(float deltaTime);
	void playerDraw(sf::RenderWindow& window);
};

