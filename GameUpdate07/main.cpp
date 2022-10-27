#include<iostream>
#include<SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Background.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include<sstream>
bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB, int currentStance, int index, int currentStanceII, int indexII) {

	const sf::Transform& TransformA(a.getInverseTransform());
	const sf::Transform& TransformB(b.getInverseTransform());

	sf::FloatRect intersection;

	if (a.getGlobalBounds().intersects(static_cast<sf::FloatRect>(b.getGlobalBounds()), intersection)) {

		sf::Vector2f vecA, vecB;
		sf::Vector2f begin, end;
		begin = { intersection.left, intersection.top };
		end = { begin.x + intersection.width, begin.y + intersection.height };


		for (int i = begin.x; i < end.x; i++) {
			for (int j = begin.y; j < end.y; j++) {
				vecA = TransformA.transformPoint(static_cast<float>(i), static_cast<float>(j));
				vecB = TransformB.transformPoint(static_cast<float>(i), static_cast<float>(j));
				vecA.x += (158 * index);
				vecA.y += (118 * currentStance);
				if ((int)imgA.getPixel(vecA.x, vecA.y).a > 0 && (int)imgB.getPixel(vecB.x, vecB.y).a > 0) {
					return true;
				}

			}
		}
	}

	return false;
}
int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Perfect Collision Test", sf::Style::Close | sf::Style::Titlebar);
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

	sf::Text text;
	sf::Font font;
	font.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(font);
	text.setCharacterSize(80);
	text.setPosition(100, 100);
	
	int counter = 0;


	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		//std::cout << deltaTime << std::endl;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) gameState = false;
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
			
				if (PixelPerfectCollision(shana.playerSprite, item.itemSprite, shana.imgPlayer, item.itemImage, shana.currentStance, shana.indexFrame[shana.currentStance], 0, item.randomIndexItem)) {
					
					if (event.key.code == sf::Keyboard::E) {
						item.setGetItem();
						++counter;
						std::stringstream ss;
						ss << "item amount : " << counter;
						text.setString(ss.str());
					}
				}

			for (int i = 0; i < enemyI.enemies.size(); i++) {
				if (PixelPerfectCollision(shana.playerSprite, enemyI.enemies[i], shana.imgPlayer, enemyI.imgEnemy, shana.currentStance, shana.indexFrame[shana.currentStance], enemyI.indexFrame[i], 0)) {
					//text.setString("Collided");
					std::cout << i <<" ";
					
				}
				else {

					//text.setString("No collide");
				}

				}
				
			
			
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
			
			gameBg.backgroundDraw(window);
			item.itemDraw(window);
			shana.playerDraw(window);
			enemyI.enemyDraw(window);
			window.draw(text);
		}

		window.display();

	}
	
	return 0;
}
