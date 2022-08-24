
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
int main() {
	sf::RenderWindow widget(sf::VideoMode(1920, 1020), "SFML!");
	sf::Vector2f mousepos;
	sf::Font f;
	f.loadFromFile("Font/GameFont.ttf");
	sf::String s;
	sf::Text newgame, scoreboard, exit, title;

	s = "SWEET HOME";
	title.setCharacterSize(100);
	title.setFillColor(sf::Color::Magenta);
	title.setFont(f);
	title.setString(s);
	title.setPosition(385, 100);


	s = "NEW GAME";
	newgame.setCharacterSize(50);
	newgame.setFillColor(sf::Color::White);
	newgame.setFont(f);
	newgame.setString(s);
	newgame.setPosition(735, 400);


	s = "SCORE BOARD";
	scoreboard.setFont(f);
	scoreboard.setCharacterSize(50);
	scoreboard.setFillColor(sf::Color::White);
	scoreboard.setString(s);
	scoreboard.setPosition(650, 550);

	s = "EXIT";
	exit.setFont(f);
	exit.setCharacterSize(50);
	exit.setFillColor(sf::Color::White);
	exit.setString(s);
	exit.setPosition(860, 700);

	while (widget.isOpen()) {

		sf::Event event;
		while (widget.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				widget.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					widget.close();
				}
			}

			if (event.type == sf::Event::MouseMoved) {
				mousepos.x = event.mouseMove.x;
				mousepos.y = event.mouseMove.y;
				std::cout << mousepos.x << " " << mousepos.y << std::endl;

				sf::FloatRect r;
				r = newgame.getGlobalBounds();
				if (r.contains(mousepos.x, mousepos.y)) {
					newgame.setFillColor(sf::Color::Yellow);

				}
				else {
					newgame.setFillColor(sf::Color::White);
					scoreboard.setFillColor(sf::Color::White);
				}

				r = scoreboard.getGlobalBounds();
				if (r.contains(mousepos.x, mousepos.y)) {
					scoreboard.setFillColor(sf::Color::Yellow);

				}
				else {
					scoreboard.setFillColor(sf::Color::White);
				}

				r = exit.getGlobalBounds();
				if (r.contains(mousepos.x, mousepos.y)) {
					exit.setFillColor(sf::Color::Yellow);

				}
				else {
					exit.setFillColor(sf::Color::White);
				}
			}

		}
		widget.clear();
		widget.draw(title);
		widget.draw(newgame);
		widget.draw(scoreboard);
		widget.draw(exit);
		widget.display();
	}
	return 0;
}
