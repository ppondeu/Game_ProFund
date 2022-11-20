#include "GamePlay.h"
GamePlay::GamePlay() {
	font.loadFromFile("Font/PixelFont2.ttf");
	title.setFont(font);
	title.setCharacterSize(characterSize);
	title.setString("GAMEPLAY");
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
	title.setPosition(1000, 600);
	title.setFillColor(sf::Color::Red);

	r.setSize(sf::Vector2f(100, 100));
	r.setFillColor(sf::Color::Red);
	r.setPosition(0, 0);
	
}

void GamePlay::draw(sf::RenderWindow& window) {
	r.move(1, 1);
	window.draw(r);
	window.draw(title);
}
