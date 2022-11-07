#pragma once
#include<iostream>
#include<sstream>
#include<queue>
#include<algorithm>
#include<SFML/Graphics.hpp>
#define WALK 0
#define ATTACK 1
#define DEATH 2
class Enemy
{
private:
	std::string enemyFile, weaponFile, figureFile;
	
	sf::Texture enemyTexture, weaponTexture, figureTexture;
	
	const sf::Vector2f enemyScale{ 3.3f, 2.0f };
	const int maxTop = 3;

	std::vector<int> maxEnemyFrame;

	sf::Vector2i imageSize;
	sf::Sprite enemySprite, weaponSprite, figureSprite;

	const float moveTime = 0.1f;
	float cntMoveTime = 0.0f;
	const float attackTime = 0.2f;
	float cntAttackTime = 0.0f;
	const float attackAgainTime = 0.5f;
	const float spawnTime = 3.0f;
	float cntSpawnTime = 0.0;
	const float frameTime = 0.15f;
	float cntFrameTime = 0.0f;
	const float deathTime = 0.2f;
	float cntDeathTime = 0.0f;
	std::vector<int> randomEnemiesPos{ 200,400,600,800 };
	std::vector<int> mode;
	std::vector<sf::Vector2f> move;

	sf::Text text;
	sf::Text healthDisplay;
	sf::Font font;
	std::vector<sf::Text> enemiesText;
	std::vector<int> hitCounterEnemy;
	std::vector<int> hitCounterPlayer;
	int healthPlayer = 1000;
	const int maxHealthPlayer = 1000;
	
	std::queue<int> indexErase;
	std::vector<bool> isDied;
	void setInfo(int mode, int top, sf::Vector2f move, int index);
	void pushEnemy();
	void popEnemy(int index);
	void setEnemyFrame(int mode);
	bool isOnScreen(int posX);
	void setHealth(int index, std::string check);
	void resetAllFrameExceptIndex(int indexEnemy, int indexTop);
	
public:
	std::vector<sf::Sprite> enemies;
	std::vector<sf::Sprite> weaponEnemies;
	std::vector<sf::Sprite> figureEnemies;
	std::vector<int> healthEnemies;
	sf::Image enemyIMG, weaponIMG, figureIMG;
	std::vector<int> top;
	std::vector<std::vector<int>> left;
	std::vector<std::vector<int>> hitEnemyFrame;
	
	Enemy(std::string enemyFile, std::string weaponFile, std::string figureFile, std::vector<int>& maxenemyFrame, 
		std::vector<std::vector<int>>& hitEnemyFrame, sf::Vector2i imageSize);
	void _Update(float deltaTime);
	void _Draw(sf::RenderWindow& window);
	void _Collided(std::string check, bool isCollided, int index);
	void _Collision(int index, bool isCollided, std::string check);
};

