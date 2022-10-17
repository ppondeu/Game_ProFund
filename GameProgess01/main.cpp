#include<iostream>
#include<SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Background.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"

int main() {
		sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen | sf::Style::Close);
		window.setFramerateLimit(60);
		
		sf::Vector2f mousePosition;
		sf::Clock clock;
		float deltaTime;

		bool gameState = false;
		bool isOpen = true;
		sf::Event event;

		Background mainMenuBg("Background/blackMenu.png");
		Background gameBg("Background/bg.png");
		MainMenu title(window, "TITLE", sf::Color::Magenta, 100, window.getSize().x / 2, 130.0f);
		MainMenu newgame(window, "NEWGAME", 1, sf::Color::White, 90);
		MainMenu scoreboard(window, "SCOREBOARD", 2, sf::Color::White, 90);
		MainMenu quit(window, "QUIT", 3, sf::Color::White, 90);
		MainMenu gameDeveloper(window, "65010539 Nitcharact Thatthiam", sf::Color::Yellow, 40, 1600.0f, 40.0f);
		
		Item item;
		
		std::vector<int> shanaFrame{ 4,4,8,8,1,1,9,9,7,7,10,10,11,11,11,11,5,5 };
		//std::vector<unsigned> heroFrame{ 4,4,8,8,1,1,9,9,7,7,10,10,11,11,11,11,5,5 };

		Player shana("Sprite/Shana.png", shanaFrame);
		
		Enemy enemyI;

		while (window.isOpen()) {
			deltaTime = clock.restart().asSeconds();
			
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) window.close();
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) window.close();
					if (event.key.code == sf::Keyboard::K) {
						shana.playerEvent("KeyPressed", "K");
					}
					if (event.key.code == sf::Keyboard::L) {
						shana.playerEvent("KeyPressed", "L");
					}
				}
				if (event.type == sf::Event::KeyReleased) {
					if (event.key.code == sf::Keyboard::L) {
						shana.playerEvent("KeyReleased", "L");
					}
					if (event.key.code == sf::Keyboard::D) {
						shana.playerEvent("KeyReleased", "D");
					}
					if (event.key.code == sf::Keyboard::A) {
						shana.playerEvent("KeyReleased", "A");
					}
					if (event.key.code == sf::Keyboard::W) {
						shana.playerEvent("KeyReleased", "W");
					}
					if (event.key.code == sf::Keyboard::S) {
						shana.playerEvent("KeyReleased", "S");
					}
					if (event.key.code == sf::Keyboard::K) {
						shana.playerEvent("KeyReleased", "K");
					}
				}
				if (event.type == sf::Event::MouseMoved) {
					mousePosition.x = event.mouseMove.x;
					mousePosition.y = event.mouseMove.y;
				}
				if (event.type == sf::Event::MouseButtonReleased) {
					if (event.key.code == sf::Mouse::Left) {
						if (gameState == false) {
							gameState = newgame.mouseButtonPressedState(mousePosition, gameState);
							isOpen = quit.mouseButtonPressedState(mousePosition, isOpen);
						}
						item.mouseButtonPressedState(mousePosition);
					}
				}
				
			}

			if (gameState == false) {
				newgame.switchColor(mousePosition);
				scoreboard.switchColor(mousePosition);
				quit.switchColor(mousePosition);
				newgame.switchColor(mousePosition);
			}
			else {
				enemyI.enemyRender(deltaTime);
				item.itemRender(deltaTime);
			}
			
			if (isOpen == false) window.close();
			shana.playerRender(deltaTime);
			window.clear(sf::Color::Green);

			if (gameState == false) {
				mainMenuBg.backgroundDraw(window);
				title.mainMenuDraw(window);
				newgame.mainMenuDraw(window);
				scoreboard.mainMenuDraw(window);
				quit.mainMenuDraw(window);
				gameDeveloper.mainMenuDraw(window);
			}
			else {
				//window.setMouseCursorVisible(0);
				gameBg.backgroundDraw(window);
				item.itemDraw(window);
				shana.playerDraw(window);
				enemyI.enemyDraw(window);
			}
			
			window.display();
				
		}


	return 0;
}
