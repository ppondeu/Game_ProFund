#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
class Player
{
private:
	std::string filename;
	std::string weaponFile;
	std::string figureFile;
	sf::Texture playerTexture;
	
	
	sf::Vector2i countImage{ 0,0 };
	sf::IntRect playerIntRect;
	
	std::vector<int> maxFrame;
	

	float totalTime = 0.0f;
	float totalTimeII = 0.0f;
	float frameTime = 0.055f;
	float idleTime = 0.13f;
	float totalTimeIII = 0.0f;
	float moveTime = 0.1f;

	float comboTime = 0.0f;
	float totalTimeIIII = 0.2f;

	std::string key;
	std::string eventType;

	sf::Vector2f move{ 0,0 };

	
	std::string side = "right";

	bool isAttack = false;
	int countPressed = 0;
	int countUltimateStance = 0;
	int countAttackStance = 0;
	int attackNo = 0;
	void setFrame();
	void resetStance();


public:
	sf::Sprite playerSprite;
	sf::Texture weaponTexture;
	sf::Sprite weaponSprite;
	sf::Texture figureTexture;
	sf::Sprite figureSprite;
	sf::Vector2i imageSize;
	int currentStance = 0;
	std::vector<int> indexFrame;
	std::vector<std::vector<int> > indexHit;
	sf::Image imgPlayer;
	sf::Image imgWeapon;
	sf::Image imgFigure;
	std::string mode = "idle";
	Player(std::string filename,std::string weaponFile, std::string figureFile, std::vector<int> &maxFrame, std::vector<std::vector<int>>& indexHit);
	void setRowColumn(sf::Vector2i countImage);
	void playerEvent(std::string Event, std::string key);
	void playerRender(float deltaTime);
	void playerDraw(sf::RenderWindow& window);
};



