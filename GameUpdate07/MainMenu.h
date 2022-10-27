#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<sstream>
class MainMenu
{
private:
	sf::Vector2f screenSize;
	sf::String stringText;
	sf::Color colorText;
	sf::Font fontText;
	sf::Text text;
	unsigned index;
	unsigned characterSize = 70;
	sf::Vector2f originText;
	sf::Vector2f positionText;
	float positionY;
	float positinX;
	void initText();
	void init();
public:
	MainMenu(sf::RenderWindow& window, sf::String stringText, sf::Color colorText, unsigned characterSize, float positionX, float positionY);
	MainMenu(sf::RenderWindow& window, sf::String stringText, unsigned index, sf::Color colorText, unsigned characterSize);
	void switchColor(sf::Vector2f mousePosition);
	bool mouseButtonPressedState(sf::Vector2f mousePosition, bool boolean);
	void mainMenuDraw(sf::RenderWindow& window);
};


