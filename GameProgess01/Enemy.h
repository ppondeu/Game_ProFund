#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>

class Enemy
{
private:

	sf::Texture texture;
	std::string fileName;
	sf::Sprite sprite;
	sf::Vector2i enemySize{ 82,48 };

	sf::Vector2f enemiesPosition;

	int maxEnemy = 10;
	int maxWalkFrame = 6;

	sf::Vector2f move{ -10.0f,0.0f };
	float totalTimeII = 0.0f;
	float spawnTime = 3.0f;

	float totalTime = 0.0f;
	float frameTime = 0.19f;

	std::vector<sf::Sprite> enemies;
	int enemyAmount = 0;
	std::vector<int> walkFrame;

public:

	Enemy();
	void enemyRender(float deltaTime);
	void enemyDraw(sf::RenderWindow& window);

};

