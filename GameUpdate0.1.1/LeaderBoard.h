#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
class LeaderBoard
{
private:
	sf::RectangleShape frame, leaderBoardFrame;
	const short maxPlayer = 5;
	std::vector<sf::RectangleShape> playerScoreFrame;

	sf::Font font;
	
	sf::RectangleShape menuFrame, playAgainFrame;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	short cntOnMenu = 0;
	short cntOnPlayAgain = 0;

	// if last state = game play state make function to request texture from the last scence of game state to display at gameoverstate;
public:
	short lastState = 0;
	sf::Text leaderBoardTxt, menuTxt, playAgainTxt;
private:
public:
	LeaderBoard();
	void isOnButton(const sf::Vector2f& mousePos);
	void onUpdate(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window);
};

