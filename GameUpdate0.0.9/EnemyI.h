#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include<queue>
#include<set>
class EnemyI
{
private:
	const short MOVE = 0;
	const short ATK = 1;
	const short DEAD = 2;

	const short LEFT = 0;
	const short RIGHT = 1;

	const short MOVE_L = 0;
	const short ATK_L = 1;
	const short ATK_R = 2;
	const short DEAD_L = 3;
	const short DEAD_R = 4;

	std::pair<const float, float > slowingTime{ 5.0f, 0.0f };
	bool isSlowing = false;
	std::set<int> indexItemErase;

	const std::string enemyFile = "Sprite/EnemyI/whole.png";
	const std::string bodyFile = "Sprite/EnemyI/body.png";
	const std::string weaponFile = "Sprite/EnemyI/weapon.png";

	sf::Texture enemyTT, bodyTT, weaponTT;

	const sf::Vector2f scale{ 2.6f, 2.0f };

	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

	const int maxLane = 3;
	const std::vector<float> spawnPos{ 218.5 + 235 - 98 - 20, 453.5 + 235 - 98 - 20, 688.5 + 235 - 98 - 20 };

	const float defaultSpeed = 50.0f;
	const float minSpeed = 10.0f;
	float speed = defaultSpeed;

	const float frameTime = 0.15f;
	float cntFrameTime = 0.0f;
	const float atkTime = 0.2f;
	float cntAtkTime = 0.0f;
	const float speedMoveTime = 0.1f;
	float cntSpeedMoveTime = 0.0f;
	const float deadTime = 0.2f;
	float cntDeadTime = 0.0f;

	float atkFrame = atkTime;
	float frame = frameTime;
	float speedMove = speedMoveTime;


	const float atkToMove = 0.0f;
	std::vector<float> cntAtkToMove;
	std::vector<bool> isEnemyDelayed;
	std::vector<int> cntOnceDelay;

	//Player Sprite
	sf::Sprite playerSP;

	// test hp enemy
	sf::Font font;
	sf::Text text;

	std::vector<sf::Text> enemyTxt;

	//

	short healthPlayer = 1000;


	std::priority_queue<int> indexErase;

	std::vector<int> itemSelected;

	short energyRegen = 0;
	short deltaHealthPlayer = 0;

	bool isSetEnemyToMoveAfterPlayerDead = false;

	short deltaScore = 0;

public:
	const sf::Vector2i imageSize{ 118, 49 };
	sf::Image enemyIMG, bodyIMG, weaponIMG;
	sf::Sprite enemySP, bodySP, weaponSP;

	std::vector<int> mode, side;
	std::vector<sf::Vector2f> move;

	const int maxTop = 5;
	const std::vector<int> maxLeft{ 6,3,3,5,5 };
	std::vector<int> top;
	std::vector<std::vector<int>> left;

	std::vector<sf::Sprite> enemyS, bodyS, weaponS;

	int cntPressedNum1 = 0;

	std::vector<int> healthEnemyS;
	std::vector<int> cntHitEnemyS;
	std::vector<int> cntHitPlayer;

	bool isEnemyDied = false;
	bool isHealthMiss = false;

	bool isPlayerDied = false;
	bool isGameOver = false;

private:
	void _push();
	void _pop(const int index);
	void setModeSideTopMove(const int mode, const int side, const int top, const sf::Vector2f move, const int index);
	void _setFrame(const int mode);
	void _setTextureRect();
	void _move();

	void checkSide(const int index);

	void setHealth(const std::string condition, const int index, const int curCombo);

	void clearEnemy();
	bool isEnemyOnScreen(sf::Vector2f enemyPos);
public:
	EnemyI();
	void onEvent(const sf::Event& event);
	void onUpdate();
	void _draw(sf::RenderWindow& window);

	void requestPlayerSprite(const sf::Sprite& playerSP);
	void _collision(const std::string condition, const bool isCollided, const int index, const int curCombo);

	short updateHealthPlayer();
	short updateEnergyPlayer();
	//bool updateScore();
	short updateScore();
	short updateHealthMiss();
	void itemAffect(const int isItemSelected);

	void updateIsPlayerDied(const bool isPlayerDied);
	void gameOver();

	


};

