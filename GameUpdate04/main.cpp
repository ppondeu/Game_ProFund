#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<random>
#include "Background.h"
#include "Item.h"
#include "PlayerMovement.h";

int main() {
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML");
	sf::Vector2f mousePos;

	//Background 
	Background BG("Bgdragonball.png");
	sf::Sprite backgroundSprite;
	backgroundSprite = BG.getSprite();
	
	//Item
	sf::RectangleShape item;
	Item IT;
	item = IT.getRect();

	//timer
	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;

	// PlayerMovement
	sf::Sprite tempPmSprite;
	PlayerMovement PM;
	tempPmSprite = PM.getPlayerSprite();
	
	while (window.isOpen()) {
		//timer
		sf::Time time = clock.getElapsedTime();
		sf::Time time2 = clock2.getElapsedTime();
		sf::Time time3 = clock3.getElapsedTime();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved) {
				mousePos.x = event.mouseMove.x;
				mousePos.y = event.mouseMove.y;
				
				//std::cout << mousePos.x << " " << mousePos.y << std::endl;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					PM.updateMoveMode('D');
					tempPmSprite = PM.getPlayerSprite();

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					PM.updateMoveMode('A');
					tempPmSprite = PM.getPlayerSprite();

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					PM.updateMoveMode('W');
					tempPmSprite = PM.getPlayerSprite();
					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

					PM.updateMoveMode('S');
					tempPmSprite = PM.getPlayerSprite();
				}
			}
		}

		if (static_cast<char>(event.text.unicode) != 'd' && static_cast<char>(event.text.unicode) != 'a' && 
			static_cast<char>(event.text.unicode) != 'w' && static_cast<char>(event.text.unicode) != 's'){
			PM.resetValue();
		}
		else if (static_cast<char>(event.text.unicode) == 'd' || static_cast<char>(event.text.unicode) == 'a' ||
			static_cast<char>(event.text.unicode) == 'w' || static_cast<char>(event.text.unicode) == 's') {
			PM.setMoveMode(static_cast<char>(event.text.unicode));
			//tempPmSprite = PM.getPlayerSprite();
		}
			
		//Is 3 seconds ?
		if (static_cast<unsigned>(time.asMilliseconds()) > 3000) {

			//Item
			IT.itemUpdate();
			item = IT.getRect();

			clock.restart();
		}

		if (static_cast <unsigned>(time2.asMilliseconds()) > 400) {
			PM.updatePlayerMovement(tempPmSprite.getPosition());
			tempPmSprite = PM.getPlayerSprite();

			clock2.restart();
		}
		
		//tempPmSprite = PM.getPlayerSprite();

		window.clear(sf::Color(150, 150, 150, 255));

		window.draw(backgroundSprite);
		window.draw(item);
		window.draw(tempPmSprite);
		
		window.display();

	}
	return 0;
}
