#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<sstream>
#include<set>
class EnemyII
{
private:
	const int MOVE = 0;
	const int ATK = 1;
	const int DEAD = 2;

	const int LEFT = 0;
	const int RIGHT = 1;

	const int MOVE_L = 0;
	const int ATK_L = 1;
	const int ATK_R = 2;
	const int DEAD_L = 3;
	const int DEAD_R = 4;

	
	const std::string enemyFile = "Sprite/EnemyII/whole.png";
	const std::string bodyFile = "Sprite/EnemyII/body.png";
	const std::string bulletFile = "Sprite/EnemyII/weapon.png";

	const float spawnTime = 5.0f;
	float cntSpawnTime = 0.0f;
	const float moveTime = 0.1f;
	float cntMoveTime = 0.0f;
	const float frameTime = 0.13f;
	float cntFrameTime = 0.0f;
	const float atkTime = 0.055f;
	float cntAtkTime = 0.0f;
	const float deadTime = 0.2f;
	float cntDeadTime = 0.2f;
	const float bulletTime = 0.08f;
	float cntBulletTime = 0.0f;
	const float speedBulletTime = 0.02f;
	float cntSpeedBulletTime = 0.0f;
	const float bulletSpawnTime = 7.0f;
	std::vector<float> cntBulletSpawnTime;

	float deltaTime;

	const float minSpeed = 50.0f;
	const float defaultSpeed = 90.0f;
	float speed = defaultSpeed;

	int cntPressedNum2=0;

	const std::vector<int> spawnPos{ 214, 414, 614 , 814 };
	const int maxLane = 4;

	sf::Sprite playerSP;

	const float defaultBulletSpeed = 7.0f;
	const float minBulletSpeed = 5.0f;
	float bulletSpeed = defaultBulletSpeed;

	// health player
	int healthPlayer = 1000;

	//tmp hp enemy
	sf::Font font;
	sf::Text text;
	std::vector<sf::Text> enemyTxt;
	//

	std::set<int> indexErase;
	std::set<int> indexBulletErase;

	

public:
	sf::Vector2i imageSize{133, 144};
	sf::Vector2i imageBulletSize{ 80,144 };

	sf::Image enemyIMG, bodyIMG, bulletIMG;
	sf::Texture enemyTT, bodyTT, bulletTT;
	sf::Sprite enemySP, bodySP, bulletSP;

	int maxTop = 5;
	std::vector<std::vector<int>> left;
	std::vector<int> maxLeft{ 4,4,4,4,4 };
	std::vector<int> side;
	std::vector<int> top;
	std::vector<int> mode;

	std::vector<sf::Sprite> enemyS, bodyS;

	std::vector<sf::Sprite> bulletS;
	std::vector<sf::Vector2f> move;
	std::vector<int> bulletTop;
	std::vector<std::vector<int>> bulletLeft;
	const int maxBulletTop = 2;
	const std::vector<int> maxBulletLeft{ 4,4 };
	std::vector<int> bulletSide;

	std::vector<int> healthEnemyS;
	

private:
	void _setTextureRect();
	void _move();
	void _push();
	void _pushBullet(const int side, const sf::Vector2f enemyPos);
	void _setFrame(const int mode);
	void _setBulletFrame();

	void checkSide(const int index);
	void setModeSideTopMove(const int mode, const int side, const int top, const sf::Vector2f move, const int index);

	bool checkLane(const int index);

	void _moveBullet();

	void _setTextureRectBullet();
	void _pushBullet();

	void setHealth(std::string condition, const int index);

	void clearBullet();
	void clearEnemy();
	void _pop(const int index);
	void _popBullet(const int index);

	bool isBulletOnScreen(const sf::Vector2f bulletPos);
	bool isEnemyOnSCcreen(const sf::Vector2f enemyPos);

	

public:
	EnemyII();
	void onEvent(const sf::Event& event);
	void onUpdate(float deltaTime);
	void _draw(sf::RenderWindow& window);

	void requestPlayerSprite(const sf::Sprite& playerSP);
	void requestHealthPlayer(const int healthPlayer);
	int updateHealthPlayer();

	void _collision(const std::string condition,const bool isCollided, const int index);

};

