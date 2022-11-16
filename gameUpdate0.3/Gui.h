#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
class Gui
{
private:
	const std::string hpMissFile = "Sprite/Gui/hpMiss.png";
	const std::string outerBarFile = "Sprite/Gui/outerBar.png";
	const std::string innerHpBarFile = "Sprite/Gui/innerHpBar.png";
	const std::string innerEnergyBarFile = "Sprite/Gui/innerEnergyBar.png";

	sf::Texture hpMissTT, outerBarTT, innerHpBarTT, innerEnergyBarTT;
	sf::Sprite hpMissSP, outerHpBarSP, outerEnergyBarSP, innerHpBarSP, innerEnergyBarSP;

	const std::string fontFile = "Font/PixelFont2.ttf";

	sf::Font font;

	sf::Text hpMissTxt, hpBarTxt, energyBarTxt, scoreTxt;

	int maxHealthPlayer;
	short healthPlayer = 1000;
	int healthMiss = 10;
	int maxEnergyPlayer = 100;
	int energyPlayer = 100;
	unsigned score = 0;
	
	std::stringstream ss;

	const float regenTime = 1.0f;
	float cntRegen = 0.0f;
	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
public:
private:
	
	void setEnergyTextureRect();
public:
	void onUpdate();
	Gui();
	void _draw(sf::RenderWindow& window);

	void requestHealthPlayer(const short deltaHealthPlayer);
	void requestScore(const unsigned score);
	void requestEnergyPlayer(const short energyPlayer);
	void requestHealthMiss(const int heathMiss);

	int updateEnergyPlayer();
};

