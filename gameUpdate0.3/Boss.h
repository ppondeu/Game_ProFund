#pragma once
#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<cassert>
class Boss
{
private:
	const int RIGHT = 0;
	const int LEFT = 1;

	const int MOVE_R = 0;
	const int MOVE_L = 1;
	const int ATK_R = 2;
	const int ATK_L = 3;
	const int EXPLOSE_ATK = 4;
	const int DEAD_R = 5;
	const int DEAD_L = 6;

	const int IDLE = 0;
	const int ATK = 1;
	const int EXPLOSE = 2;
	const int DEAD = 3;

	const std::string bossFile = "Sprite/Boss/whole.png";
	const std::string bodyFile = "Sprite/Boss/bodyS.png";
	const std::string bulletFile = "Sprite/Boss/bullet.png";

	sf::Texture bossTT, bodyTT, bulletTT;

	sf::Vector2f scale{ 1,1 };

	const float frameTime = 0.1f;
	float cntFrameTime = 0.0f;

	const float moveTime = 0.1f;
	float cntMoveTime = 0.0f;

	const float atkTime = 0.055f;
	float cntAtkTime = 0.0f;

	const float deadTime = 0.2f;
	float cntDeadTime = 0.0f;



	const float idleToExploseTime = 3.0f;
	float cntIdleToExplose = 0.0f;
	bool isIdleToExplose = false;

	bool isExploseToBullet = false;
	bool isShotBullet = false;
	const float bulletDelayTime = 1.0f;
	float cntBulletDelay = 0.0f;
	
	const float exploseTime = 0.1f;
	float cntExploseTime = 0.0f;



	const float defaultSpeed = 10.0f;
	const float minSpeed = 7.0f;
	const float defaultVerticalSpeed = 10.0f;
	const float minVerticalSpeed = 7.0f;

	float speed = defaultSpeed;
	float verticalSpeed = defaultVerticalSpeed;

	sf::Vector2f move{ speed, verticalSpeed };

	sf::Vector2f playerPos{ 500.0f, 500.0f };
	float deltaTime;
	float distance = 0.0f;
	sf::Vector2f dir;

	sf::Clock clock2;
	sf::Time timeElapsed = sf::Time::Zero;
	sf::Time duration = sf::Time::Zero;

	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	sf::Sprite playerSP;
	int playerSide;

	const int maxBullet = 3;
	int cntBullet = 0;
public:
	sf::Image bossIMG, bodyIMG, bulletIMG;
	sf::Sprite bossSP, bodySP, bulletSP;

	sf::Vector2i imageSize{ 172, 180 };

	int maxTop = 7;
	int top = MOVE_L;
	int side = LEFT;
	int mode = IDLE;
	std::vector<int> left;
	std::vector<int> maxLeft{ 3,3,10,10,10,5,5 };
	int curCombo = MOVE_L;

	int maxWeaponTop = 4;
	int weaponTop = curCombo - 1;
	std::vector<int> weaponLeft;
	std::vector<int> maxWeaponLeft{ 10,10,10,10 };


private:
	void _setTextureRect();
	void _move();

	void setModeSideTopMove(int mode, int side, int top, sf::Vector2f move);
	void setFrame(int mode);

	void pushBullet();

	void resetFrame(const int top);
	
	
public:
	Boss();
	void onUpdate(float deltaTime);
	void _draw(sf::RenderWindow& window);

	void requestPlayerPos(sf::Vector2f playerPos);

	void requestPlayerSprite(const sf::Sprite& playerSP);
	void requestPlayerSide(const int playerSide);
	
};

