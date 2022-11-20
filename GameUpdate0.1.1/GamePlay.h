#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Text.h"
class GamePlay
{
private:
	sf::Font font;
	sf::Text title, play, tutorial, leaderboard, exit;
	const unsigned short characterSize = 90;

	sf::RectangleShape r;
public:
	Text t;
private:
public:
	GamePlay();
	void draw(sf::RenderWindow& window);
};

