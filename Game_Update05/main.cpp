#include<iostream>
#include<SFML/Graphics.hpp>
#include "Background.h"
#include "Item.h"
#include "Enemy.h"
#include "Player.h"

int main() {
	srand(static_cast<unsigned>(time(0)));

	sf::RenderWindow window(sf::VideoMode(1920, 1000), "SFML", sf::Style::Fullscreen | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(0, 0));

	sf::Event event;

	sf::Clock clock;
	float deltaTime = 0.0f;

	Background background;

	Item item;

	Enemy enemy;

	Player player;

	while (window.isOpen()) {
		
		deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

		item.itemRender(deltaTime);
		enemy.enemyRender(deltaTime);
		player.playerRender(deltaTime);

		window.clear(sf::Color::Green);

		background.backgroundDraw(window);
		item.itemDraw(window);
		enemy.enemyDraw(window);
		player.playerDraw(window);

		window.display();

	}
	
	return 0;

}
