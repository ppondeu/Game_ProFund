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

	int idx = 0;
	std::vector<std::string> defaultFilename{ "default1.png", "default2.png", "default3.png", "default4.png" };
	sf::Texture tdefault;
	tdefault.loadFromFile(defaultFilename[idx]);
	sf::Vector2f playerPos(400, 400);
	sf::Sprite spDefault;
	spDefault.setTexture(tdefault);
	spDefault.setPosition(playerPos);
	spDefault.setScale(1.5f, 2.25f);

	sf::Texture fly;
	fly.loadFromFile("fly.png");
	sf::Sprite spFly;
	spFly.setTexture(fly);
	spFly.setScale(1.5f, 2.25f);

	std::string mode = "default";
	sf::Sprite tmpSprite;
	tmpSprite = spDefault;

	int counterStepD = 0;
	int counterStepA = 0;
	int counterStepW = 0;
	int counterStepS = 0;

	PlayerMovement PM("fly.png");
	sf::Sprite playerMovementSprite;
	playerMovementSprite = PM.getTempSprite();
	
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
					//mode = "move";
					++counterStepD;
					counterStepA = 0;
					counterStepW = 0;
					counterStepS = 0;
					/*if (mode == "move" && counterStepD > 1) {
						playerPos = tmpSprite.getPosition();
						playerPos.x += 10;
						spFly.setPosition(playerPos);
						tmpSprite = spFly;
					}*/
					if (mode == "move" && counterStepD > 1) {
						PM.updateFly('D');
						playerMovementSprite = PM.getTempSprite();
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					//mode = "move";
					++counterStepA;
					counterStepD = 0;
					counterStepW = 0;
					counterStepS = 0;
					/*if (mode == "move" && counterStepA > 1) {
						playerPos = tmpSprite.getPosition();
						playerPos.x -= 10;
						spFly.setPosition(playerPos);
						tmpSprite = spFly;
					}*/
					if (mode == "move" && counterStepA > 1) {
						PM.updateFly('A');
						playerMovementSprite = PM.getTempSprite();
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					//mode = "move";
					++counterStepW;
					counterStepA = 0;
					counterStepD = 0;
					counterStepS = 0;
					/*if (mode == "move" && counterStepW > 1) {
						playerPos = tmpSprite.getPosition();
						playerPos.y -= 10;
						spFly.setPosition(playerPos);
						tmpSprite = spFly;
					}*/
					if (mode == "move" && counterStepW > 1) {
						PM.updateFly('W');
						playerMovementSprite = PM.getTempSprite();
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					mode = "move";
					++counterStepS;
					counterStepA = 0;
					counterStepD = 0;
					counterStepW = 0;
					/*if (mode == "move" && counterStepS > 1) {
						playerPos = tmpSprite.getPosition();
						playerPos.y += 10;
						spFly.setPosition(playerPos);
						tmpSprite = spFly;
					}*/
					if (mode == "move" && counterStepS > 1) {
						PM.updateFly('S');
						playerMovementSprite = PM.getTempSprite();
					}
				}
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128) {
					if (static_cast<char>(event.text.unicode) == 'd') {
						//std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
					}

				}
			}
		}
		if (static_cast<char>(event.text.unicode) != 'd' && static_cast<char>(event.text.unicode) != 'a' && 
			static_cast<char>(event.text.unicode) != 'w' && static_cast<char>(event.text.unicode) != 's'){
			mode = "default";
			counterStepA = 0;
			counterStepD = 0;
			counterStepW = 0;
			counterStepS = 0;
		}
		else if (static_cast<char>(event.text.unicode) == 'd' || static_cast<char>(event.text.unicode) == 'a' ||
			static_cast<char>(event.text.unicode) == 'w' || static_cast<char>(event.text.unicode) == 's') {
			mode = "move";
		}
			

		//Is 3 seconds ?
		if (static_cast<unsigned>(time.asMilliseconds()) > 3000) {

			//Item
			IT.itemUpdate();
			item = IT.getRect();

			clock.restart();
		}

		if (static_cast <unsigned>(time2.asMilliseconds()) > 400) {
			if (mode == "default") {
				/*++idx;
				if (idx >= 4) {
					idx = 0;
				}
				tdefault.loadFromFile(defaultFilename[idx]);
				spDefault.setTexture(tdefault);
				playerPos = tmpSprite.getPosition();
				spDefault.setPosition(playerPos);
				tmpSprite = spDefault;*/

				PM.updateDefault();
				playerMovementSprite = PM.getTempSprite();
			}
			else if(mode=="fly") {
				/*playerPos = tmpSprite.getPosition();
				spFly.setPosition(playerPos);
				tmpSprite = spFly;*/

				PM.updatePlayerPosition(mode);
				playerMovementSprite = PM.getTempSprite();
			}
			clock2.restart();
		}
		playerPos = spDefault.getPosition();

		window.clear(sf::Color(150, 150, 150, 255));

		window.draw(backgroundSprite);
		window.draw(item);
		//window.draw(tmpSprite);
		window.draw(playerMovementSprite);

		window.display();

	}
	return 0;
}
