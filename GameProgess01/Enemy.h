#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>

class Enemy
{
private:
	std::string filename;
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;

	std::vector<sf::Sprite> enemies;
	int maxWalkFrame = 6;
	int maxEnemySpawn = 10;
	int countEnemy = 0;
	std::vector<int> indexFrame;
	float totalTimeI = 0.0f;
	float totalTimeII = 0.0f;
	float frameTime = 0.1f;
	float spawnTime = 3.f;

	sf::Vector2i imageSize;
	sf::Vector2i countImage;
	sf::Vector2f enemyPosition;
	sf::Vector2f move{ -7.0f, 0.0f };
	void pushbackEnemy();
	void setEnemy();
	bool isOnTheScreen(int enemyPositionX);
public:

	Enemy();
	void enemyRender(float deltaTime);
	void enemyDraw(sf::RenderWindow& window);

};

