#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
class Gui
{
private:
	const std::string hpMissFile = "Sprite/Gui/life.png";
	const std::string outerBarFile = "Sprite/Gui/outer.png";
	const std::string innerHpBarFile = "Sprite/Gui/hp.png";
	const std::string innerEnergyBarFile = "Sprite/Gui/energy.png";
	const std::string hpIconFile = "Sprite/Gui/hpIcon.png";
	const std::string energyIconFile = "Sprite/Gui/energyIcon.png";

	sf::Texture hpMissTT, outerBarTT, innerHpBarTT, innerEnergyBarTT, hpIconTT, energyIconTT;
	sf::Sprite hpMissSP, outerHpBarSP, outerEnergyBarSP, innerHpBarSP, innerEnergyBarSP, hpIconSP, energyIconSP;
	
	const std::string fontFile = "Font/PixelFont2.ttf";

	sf::Font font;

	sf::Text hpMissTxt, hpBarTxt, energyBarTxt, scoreTxt;

	short maxHealthPlayer = 1000;
	short healthPlayer = maxHealthPlayer;
	int healthMiss = 10;
	int maxEnergyPlayer = 100;
	int energyPlayer = 100;
	unsigned long long score = 0;

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
	void requestScore(const short deltaScore);
	void requestEnergyPlayer(const short energyPlayer);
	void requestHealthMiss(const int heathMiss);

	int updateEnergyPlayer();
};


