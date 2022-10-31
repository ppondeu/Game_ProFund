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
	int maxEnemySpawn = 100;
	int countEnemy = 0;
	
	float totalTimeI = 0.0f;
	float totalTimeII = 0.0f;
	float frameTime = 0.1f;
	float spawnTime = 1.f;

	
	
	sf::Vector2f enemyPosition;
	sf::Vector2f move{ -10.0f, 0.0f };
	sf::Text tmpText;
	sf::Font font;
	std::vector<int> hitCounter;
	std::vector<int> enemyFrame;
	std::vector<int> top;
	void pushbackEnemy();
	void setEnemy();
	void eraseEnemy(int index);
	bool isOnScreen(int enemyPositionX);
/*void enemyAttack(int index);
	void enemyStance(int index, std::string mode);
	void enemyWalk(int index);
	void enemyDeath(int index);*/
public:
	std::vector<int> indexFrame;
	sf::Vector2i imageSize;
	sf::Vector2i countImage;
	std::vector<sf::Sprite> enemies;
	sf::Image imgEnemy;
	std::vector<int> health;
	std::vector<int> damageRecieved;
	std::vector<sf::Text> t;
	std::vector<int> randPos{200, 400 , 600, 800};
	Enemy();
	//Enemy(std::string enemyFile, std::vector<int>& enemyFrame);
	void collision(int index, bool isCollide, int currentStance, int indexFrame);
	void enemyRender(float deltaTime);
	void enemyDraw(sf::RenderWindow& window);
	

};



