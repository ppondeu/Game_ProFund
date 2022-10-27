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

	
	int maxWalkFrame = 6;
	int maxEnemySpawn = 10;
	int countEnemy = 0;
	
	float totalTimeI = 0.0f;
	float totalTimeII = 0.0f;
	float frameTime = 0.1f;
	float spawnTime = 1.f;

	
	
	sf::Vector2f enemyPosition;
	sf::Vector2f move{ -10.0f, 0.0f };
	void pushbackEnemy();
	void setEnemy();
	bool isOnScreen(int enemyPositionX);
public:
	std::vector<int> indexFrame;
	sf::Vector2i imageSize;
	sf::Vector2i countImage;
	std::vector<sf::Sprite> enemies;
	sf::Image imgEnemy;
	Enemy();
	void enemyRender(float deltaTime);
	void enemyDraw(sf::RenderWindow& window);

};


