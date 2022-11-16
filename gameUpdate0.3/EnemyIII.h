#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include<queue>
#include<set>
class EnemyIII
{
private:
	const unsigned short MOVE = 0;
	const unsigned short ATK = 1;
	const unsigned short DEAD = 2;

	const unsigned short LEFT = 0;
	const unsigned short RIGHT = 1;

	const unsigned short MOVE_L = 0;
	const unsigned short ATK_L = 1;
	const unsigned short ATK_R = 2;
	const unsigned short DEAD_L = 3;
	const unsigned short DEAD_R = 4;

	std::pair<const float, float > slowingTime{ 5.0f, 0.0f };
	bool isSlowing = false;
	std::set<int> indexItemErase;

	const std::string enemyFile = "Sprite/EnemyIII/whole.png";
	const std::string bodyFile = "Sprite/EnemyIII/body.png";
	const std::string weaponFile = "Sprite/EnemyIII/weapon.png";

	sf::Texture enemyTT, bodyTT, weaponTT;

	const sf::Vector2f scale{ 3.f, 3.f };

	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

	const int maxLane = 4;
	const std::vector<int> spawnPos{ 214, 414, 614 , 814 };

	const float defaultSpeed = 30.0f;
	const float minSpeed = 10.0f;
	float speed = defaultSpeed;

	const float frameTime = 0.15f;
	float cntFrameTime = 0.0f;
	const float atkTime = 0.15f;
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

	unsigned short energyRegen = 0;
	short deltaHealthPlayer = 0;

	bool check = false;

public:
	const sf::Vector2i imageSize{ 129, 76 };
	sf::Image enemyIMG, bodyIMG, weaponIMG;
	sf::Sprite enemySP, bodySP, weaponSP;

	std::vector<int> mode, side;
	std::vector<sf::Vector2f> move;

	const int maxTop = 5;
	const std::vector<int> maxLeft{ 6,6,6,4,4 };
	std::vector<int> top;
	std::vector<std::vector<int>> left;

	std::vector<sf::Sprite> enemyS, bodyS, weaponS;

	int cntPressedNum3 = 0;

	std::vector<int> healthEnemyS;
	std::vector<int> cntHitEnemyS;
	std::vector<int> cntHitPlayer;

	bool isEnemyDied = false;
	bool isHealthMiss = false;

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
	EnemyIII();
	void onEvent(const sf::Event& event);
	void onUpdate();
	void _draw(sf::RenderWindow& window);

	void requestPlayerSprite(const sf::Sprite& playerSP);
	void _collision(const std::string condition, const bool isCollided, const int index, const int curCombo);

	short updateHealthPlayer();
	unsigned short updateEnergyPlayer();
	void requestHealthPlayer(const short healthPlayer);
	bool updateScore();
	unsigned short updateHealthMiss();
	void itemAffect(const int isItemSelected);

};

