#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<iostream>
#include<cctype>
class EnterName
{
private:
	sf::Font font;
	sf::Text victoryTxt, defeatTxt;
	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Text scoreTxt;
	sf::RectangleShape NameBox, submitBox;
	short cntOnSubmit = 0;

	sf::Text textEnter;
	std::stringstream textEnterSS;
	
public:
	short resultState = 0;   // 0->defeat , 1->victory, 2->process
	unsigned long long score = 0;
	sf::Text submitTxt;
	std::string textEnterStr;
private:
	
public:
	EnterName();
	void onEvent(const sf::Event& event);
	void isOnButton(const sf::Vector2f& mousePos);
	void onUpdate(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window);
};

