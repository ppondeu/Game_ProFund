#include<SFML/Graphics.hpp>
#include<iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML");
	sf::Vector2f mousePos;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if(event.type ==  sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved) {
				mousePos.x = event.mouseMove.x;
				mousePos.y = event.mouseMove.y;
				std::cout << mousePos.x << " " << mousePos.y << std::endl;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close();
				}
			}
		}

		window.clear(sf::Color(150, 150, 150, 255));
		window.display();

	}

	return 0;
}
