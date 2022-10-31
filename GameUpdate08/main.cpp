#include<iostream>
#include<SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Background.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include<sstream>
bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Sprite& weapon, const sf::Sprite& figure, const sf::Image& imgA, const sf::Image& imgB,
	const sf::Image& imgWeapon, const sf::Image& imgFigure, int currentStance, int index, int currentStanceII, int indexII) {

	const sf::Transform& TransformA(a.getInverseTransform());
	const sf::Transform& TransformB(b.getInverseTransform());
	const sf::Transform& TransformWeapon(weapon.getInverseTransform());
	const sf::Transform& TransformFigure(figure.getInverseTransform());
	sf::FloatRect intersection, intersectionII, intersectionIII;
	if (a.getGlobalBounds().intersects(static_cast<sf::FloatRect>(b.getGlobalBounds()), intersection)) {
		intersectionII = intersectionIII = intersection;

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

bool PixelPerfectCollision2(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB,
	int currentStance, int index, int currentStanceII, int indexII) {

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
	window.setFramerateLimit(144);
	sf::Vector2f mousePosition;
	sf::Clock clock;
	float deltaTime;

	bool gameState = false;
	bool isOpen = true;
	sf::Event event;

	Background mainMenuBg("Background/blackMenu.png");
	Background gameBg("Background/ruinBG.png");
	MainMenu title(window, "TITLE", sf::Color::Magenta, 100, window.getSize().x / 2, 130.0f);
	MainMenu newgame(window, "NEWGAME", 1, sf::Color::White, 90);
	MainMenu scoreboard(window, "SCOREBOARD", 2, sf::Color::White, 90);
	MainMenu quit(window, "QUIT", 3, sf::Color::White, 90);
	MainMenu gameDeveloper(window, "65010539 Nitcharact Thatthiam", sf::Color::Yellow, 40, 1600.0f, 40.0f);

	Item* item = new Item;

	std::vector<int> shanaFrame{ 4,4,8,8,1,1,9,9,7,7,10,10,11,11,11,11,5,5 };
	std::vector<int> shanaFrame2{ 4,4,8,8,1,1,9,9,7,7,10,10,11,11,11,11,10,10,5,5 };
	//std::vector<unsigned> heroFrame{ 4,4,8,8,1,1,9,9,7,7,10,10,11,11,11,11,5,5 };

	std::vector< std::vector<int> > indexHit{ {0}, {0}, {0}, {0}, {0}, {0},
		{4,5,6},{4,5,6} ,{2,3,4}, {2,3,4}, {3,4,5,6,7,8,9}, {3,4,5,6,7,8,9}, {3,4,5,6,7}, {3,4,5,6,7}, {4,5,6,7}, {4,5,6,7},
		{0}, {0}, {0}, {0} };

	Player* shana = new Player("Sprite/r.png", "Sprite/weaponShana.png", "Sprite/figureShana.png", shanaFrame2, indexHit);
	
	Enemy* enemyI = new Enemy;

	sf::Text text;
	sf::Font font;
	font.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(font);
	text.setCharacterSize(80);
	text.setPosition(100, 100);

	int counter = 0;

	bool isPaused = false;

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		//std::cout << deltaTime << std::endl;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) gameState = false;
				if (event.key.code == sf::Keyboard::K) {
					shana->playerEvent("KeyPressed", "K");
				}
				if (event.key.code == sf::Keyboard::J) {
					shana->playerEvent("KeyPressed", "J");
				}
				if (event.key.code == sf::Keyboard::X) {
					shana->playerEvent("KeyPressed", "X");

				}
				if (event.key.code == sf::Keyboard::E) {
					if (gameState == false) {
						gameState = true;
						item = new Item;

						shana = new Player("Sprite/r.png", "Sprite/weaponShana.png", "Sprite/figureShana.png", shanaFrame2, indexHit);

						enemyI = new Enemy;
					}
				}
				if (event.key.code == sf::Keyboard::P) {
					isPaused = !isPaused;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::X) {

					shana->playerEvent("KeyReleased", "X");
				}
				if (event.key.code == sf::Keyboard::J) {
					shana->playerEvent("KeyReleased", "J");
				}
				if (event.key.code == sf::Keyboard::D) {
					shana->playerEvent("KeyReleased", "D");
				}
				if (event.key.code == sf::Keyboard::A) {
					shana->playerEvent("KeyReleased", "A");
				}
				if (event.key.code == sf::Keyboard::W) {
					shana->playerEvent("KeyReleased", "W");
				}
				if (event.key.code == sf::Keyboard::S) {
					shana->playerEvent("KeyReleased", "S");
				}
				if (event.key.code == sf::Keyboard::K) {
					shana->playerEvent("KeyReleased", "K");
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
					item->mouseButtonPressedState(mousePosition);
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
			if (isPaused) {
				deltaTime = 0;
			}

			if (PixelPerfectCollision2(shana->playerSprite, item->itemSprite, shana->imgPlayer, item->itemImage, shana->currentStance, shana->indexFrame[shana->currentStance], 0, item->randomIndexItem)) {

				if (event.key.code == sf::Keyboard::E) {
					item->setGetItem();
					++counter;
					std::stringstream ss;
					ss << "item amount : " << counter;
					text.setString(ss.str());
				}
			}

			for (int i = 0; i < enemyI->enemies.size(); i++) {

				if (PixelPerfectCollision2(shana->weaponSprite, enemyI->enemies[i],
					shana->imgWeapon, enemyI->imgEnemy, shana->currentStance, shana->indexFrame[shana->currentStance], enemyI->indexFrame[i], 0)) {
					if (indexHit.at(shana->currentStance).size() > 1) {
						for (auto& e : indexHit.at(shana->currentStance)) {
							if (shana->indexFrame[shana->currentStance] == e) {
								//enemies was attacked
								//std::cout << e << " hitted" << std::endl;
								std::stringstream ss;
								++counter;
								ss << i << " " << " " << e << "item amount : " << counter;
								text.setString(ss.str());
								enemyI->collision(i, true, shana->currentStance, shana->indexFrame[shana->currentStance]);
								
							}
						}
					}
					
					//std::cout << i << " hited" << std::endl;
					text.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
				}
				else {
					enemyI->collision(i, false, shana->currentStance , shana->indexFrame[shana->currentStance]);
					//text.setString("No collide");
				}
			}



			enemyI->enemyRender(deltaTime);
			item->itemRender(deltaTime);
		}

		if (isOpen == false) window.close();
		shana->playerRender(deltaTime);
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
			item->itemDraw(window);

			shana->playerDraw(window);
			enemyI->enemyDraw(window);
			window.draw(text);
		}

		window.display();

	}



	return 0;
}
