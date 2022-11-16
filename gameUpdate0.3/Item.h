#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<sstream>

class Item
{
private:
	const unsigned short RAZE = 0;
	const unsigned short SLOWING = 0;
	const unsigned short LIGHTNING = 0;
	const unsigned short HEALING = 0;

	const std::string itemFile = "Sprite/Item/item.png";
	const std::string itemBarFile = "Sprite/Item/itemBar.png";

	sf::Texture itemTT;

	const unsigned short maxItem = 4;

	sf::Vector2f randPos;
	unsigned short randItem;


	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
	const float cooldownTime = 3.0f;
	float cntCooldown = 0.0f;

	sf::Texture itemBarTT;
	sf::Sprite itemBarSP;
	sf::Vector2i imageItemBarSize{ 120, 100 };
	std::vector<unsigned short> amountItem;

	sf::Text amount;
	sf::Font font;

	std::vector<sf::Sprite> itemBar;
	std::vector<sf::Text> amountItemTxt;

	bool isCollided = false;

	unsigned short cntPressedE = 0;
	unsigned short cntPressedI = 0;
	unsigned short cntPressedEnter = 0;

	//crop item bar
	sf::RectangleShape itemBarCrop;
	//

	bool isSelectedItem = false;

	const float selectFadeAwayTime = 3.0f;
	float cntSelectFadeAway = 0.0f;

	unsigned short tempItemCrop = 0;
	unsigned short tempOfTemp = 0;

	unsigned short itemSelected = 666;

private:
	void setFrame();
	void random();

	void setItemBarCropFrame();

	void resetCropInfo();

public:
	sf::Image itemIMG;
	sf::Sprite itemSP;

	unsigned short currentItem = 0;
	const sf::Vector2i imageSize{ 100, 100 };

public:
	Item();
	void onUpdate();
	void onEvent(const sf::Event& event);
	void _draw(sf::RenderWindow& window);

	void collision(const bool isCollided);
	
	unsigned short getItemSelected();
	void resetItemSelected();
};

