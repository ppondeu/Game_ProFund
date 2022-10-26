#include<SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>

bool PixelPerfectCollision(const sf::RectangleShape& a, const sf::RectangleShape& b, const sf::Image& imgA, const sf::Image& imgB) {

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
				if ((int)imgA.getPixel(vecA.x, vecA.y).a > 0 && (int)imgB.getPixel(vecB.x, vecB.y).a > 0) {
					return true;
				}

			}
		}
	}

	return false;
}


int main() {
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML", sf::Style::Default | sf::Style::Close);
	sf::Vector2f mousePos;
	
	window.setPosition(sf::Vector2i(990, 0));
	window.setFramerateLimit(120);

	//timer
	sf::Clock clock;
	
	sf::Image image;
	image.loadFromFile("test3.png");
	
	
	
	int counter = 0;
	
	for (int i = 0; i < image.getSize().y; i++) {
		for (int j = 0; j < image.getSize().x; j++) {
			if (sf::Color::Transparent != image.getPixel(j, i)) {
				//std::cout << i << " " << j << std::endl;
				++counter;

			}
		}
	}
	//std::cout << counter << std::endl;

	sf::Vector2f size{ 168,166 };

	sf::Texture T1;
	T1.loadFromFile("Yellow.png");
	sf::RectangleShape SP1;
	SP1.setTexture(&T1);
	SP1.setPosition(168, 166);
	sf::Image IMG1;
	IMG1.loadFromFile("Yellow.png");
	SP1.setSize(size);
	sf::Texture T2;
	T2.loadFromFile("Green.png");
	sf::RectangleShape SP2;
	SP2.setTexture(&T2);
	SP2.setPosition(400, 400);
	sf::Image IMG2;
	IMG2.loadFromFile("Green.png");
	SP2.setSize(size);
	
	sf::FloatRect intersection;

	sf::Sprite Test;
	

	sf::RectangleShape outline, outline2;
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineColor(sf::Color::Red);
	outline.setOutlineThickness(1);
	outline.setSize(size);
	outline2 = outline;

	outline.setPosition(SP1.getPosition());
	outline2.setPosition(SP2.getPosition());


	sf::Text text;
	sf::Font font;
	font.loadFromFile("PixelFont2.ttf");
	text.setFont(font);
	text.setPosition(50, 50);
	text.setCharacterSize(80);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseMoved) {
				mousePos.x = event.mouseMove.x;
				mousePos.y = event.mouseMove.y;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) SP1.move(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) SP1.move(-1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) SP1.move(0, 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) SP1.move(1, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) SP2.move(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) SP2.move(-1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) SP2.move(0, 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) SP2.move(1, 0);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			SP1.setPosition(SP2.getPosition());
		}  

		if (PixelPerfectCollision(SP1, SP2, IMG1, IMG2)) {
			text.setString("Collide");
		}
		else {
			text.setString("No collide");
		}
		
		
		
		window.clear(sf::Color(44, 47, 51));
		window.draw(SP1);
		window.draw(SP2);
		window.draw(text);
		window.display();
	}
	
	return 0;
}
