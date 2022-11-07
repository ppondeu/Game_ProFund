#pragma once
#include<iostream>
#include<sstream>
#include<SFML/Graphics.hpp>
#define IDLE 0
#define MOVE 1
#define ATTACK 2
#define DEATH 3
#define RIGHT 0
#define LEFT 1
class Player
{
private:
	
	sf::Texture playerTexture, weaponTexture, figureTexture;
	
	const sf::Vector2f playerScale{ 2.6f, 2.0f };
	const int maxTop = 20;
	
	sf::Vector2f move{0.0f, 0.0f};
	sf::Vector2i mousePos;
	int mode = IDLE;
	int side = RIGHT;
	const float idleTime = 0.13f;
	float cntIdleTime = 0.0f;
	const float moveTime = 0.1f;
	float cntMoveTime = 0.0f;
	const float attackTime = 0.055f;
	float cntAttackTime = 0.0f;
	const float comboTime = 0.85f;
	float cntComboTime = 0.0f;
	
	int cntPressed = 0;
	bool isAttack = false;
	std::vector<int> comboDefault{6,8,10};
	std::vector<int> comboRage{ 12,14 };
	int comboRun = 0;
	void setInfo(int mode, int side, int top, sf::Vector2f move);
	void resetAllFrameExceptIndex(int index);
public:
	std::string playerFile, weaponFile, figureFile;
	std::vector<int> maxPlayerFrame;
	std::vector<std::vector<int>> hitPlayerFrame;
	sf::Image playerIMG, weaponIMG, figureIMG;
	sf::Vector2i imageSize;
	sf::Sprite playerSprite, weaponSprite, figureSprite;
	int top;
	std::vector<int> left;
	Player(std::string playerFile, std::string weaponFile, std::string figureFile, std::vector<int>& maxPlayerFrame, std::vector<std::vector<int>>&hitPlayerFrame, sf::Vector2i imageSize);
	void _OnEvent(sf::RenderWindow& window, sf::Event& evnt);
	void _Update(float deltaTime, sf::Vector2i& mousePos);
	void _Draw(sf::RenderWindow& window);
	
	
};

