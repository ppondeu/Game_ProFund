#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include"Player.h"
#include "Enemy.h"
#include<sstream>
#include<queue>
bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB, int topA, int leftA, int topB, int leftB, sf::Vector2i sizeA, sf::Vector2i sizeB);

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "GAME!", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	sf::Clock mainClock;
	float deltaTime;
	sf::Vector2i mousePos;

	std::vector<int>maxShanaFrame{ 4,4,8,8,1,1,9,9,7,7,10,10,11,11,11,11,10,10,5,5 };
	std::vector<std::vector<int>> hitShanaFrame{ {0}, {0}, {0}, {0}, {0}, {0},
		{4,5,6},{4,5,6} ,{2,3,4}, {2,3,4}, {3,4,5,6,7,8,9}, {3,4,5,6,7,8,9}, {3,4,5,6,7}, {3,4,5,6,7}, {4,5,6,7}, {4,5,6,7},
		{0}, {0}, {0}, {0} };
	
	Player* _Shana = new Player("Sprite/shana.png", "Sprite/weapon_shana.png", "Sprite/figure_shana.png",maxShanaFrame, hitShanaFrame, {158,119});

	std::vector<int> maxSkeletonFrame{ 6,3,5 };
	std::vector<std::vector<int>> hitSkeletonFrame{ {0}, {1,2}, {0} };

	Enemy* _Skeleton = new Enemy("Sprite/skeleton.png", "Sprite/weapon_skeleton.png", "Sprite/figure_skeleton.png", maxSkeletonFrame, hitSkeletonFrame, { 75,49 });

	sf::Texture outside, inside;
	outside.loadFromFile("Sprite/outside.png");
	inside.loadFromFile("Sprite/inside.png");
	sf::Sprite outSprite, inSprite;
	outSprite.setTexture(outside);
	inSprite.setTexture(inside);
	outSprite.setOrigin(outside.getSize().x / 2, outside.getSize().y / 2);
	inSprite.setOrigin(inside.getSize().x / 2, inside.getSize().y / 2);
	outSprite.setPosition(525, 45);
	inSprite.setPosition(525, 45);

	sf::Texture miss;
	miss.loadFromFile("Sprite/miss.png");
	sf::Sprite missSprite;
	missSprite.setTexture(miss);
	missSprite.setOrigin(miss.getSize().x / 2, miss.getSize().y / 2);
	missSprite.setPosition(1200, 75);

	while (window.isOpen()) {
		deltaTime = mainClock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseMoved) {
				mousePos = { static_cast<int>(event.mouseMove.x), static_cast<int>(event.mouseMove.y) };
			}
			_Shana->_OnEvent(window, event);
		}

		_Shana->_Update(deltaTime, mousePos);
		_Skeleton->_Update(deltaTime);


		for (int i = 0; i < _Skeleton->enemies.size(); i++) {
			if (PixelPerfectCollision(_Skeleton->enemies[i], _Shana->playerSprite, _Skeleton->enemyIMG, _Shana->playerIMG,
				_Skeleton->top[i], _Skeleton->left[i][_Skeleton->top[i]], _Shana->top, _Shana->left[_Shana->top], { 75, 49 }, { 158, 119 })) {
				_Skeleton->_Collided("ENEMY V PLAYER", true, i);
			}
			else {
				_Skeleton->_Collided("ENEMY V PLAYER", false, i);
			}

			if (PixelPerfectCollision(_Shana->weaponSprite, _Skeleton->figureEnemies[i], _Shana->weaponIMG, _Skeleton->figureIMG, _Shana->top, _Shana->left[_Shana->top], _Skeleton->top[i], _Skeleton->left[i][_Skeleton->top[i]], { 158, 119 }, { 75, 49 })) {
				if (_Shana->hitPlayerFrame[_Shana->top].size() > 1) {
					for (auto& e : _Shana->hitPlayerFrame[_Shana->top]) {
						if (_Shana->left[_Shana->top] == e) {
							_Skeleton->_Collision(i, true, "ENEMY");
						}
					}
				}
			}
			else {
				_Skeleton->_Collision(i, false, "ENEMY");
			}
			if (PixelPerfectCollision(_Skeleton->weaponEnemies[i], _Shana->figureSprite, _Skeleton->weaponIMG, _Shana->figureIMG,
				_Skeleton->top[i], _Skeleton->left[i][_Skeleton->top[i]], _Shana->top, _Shana->left[_Shana->top], { 75, 49 }, { 158, 119 })) {

				_Skeleton->_Collision(i, true, "PLAYER");

			}
			else {
				_Skeleton->_Collision(i, false, "PLAYER");
			}

		}

		window.clear(sf::Color(100, 100, 255, 255));
		window.draw(outSprite);
		window.draw(inSprite);
		window.draw(missSprite);
		_Shana->_Draw(window);
		
		_Skeleton->_Draw(window);
		
		window.display();

	}
	return 0;
}

bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB, int topA, int leftA, int topB, int leftB, sf::Vector2i sizeA, sf::Vector2i sizeB) {

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
				vecA.x += (sizeA.x * leftA);
				vecA.y += (sizeA.y * topA);
				vecB.x += (sizeB.x * leftB);
				vecB.y += (sizeB.y * topB);
				if ((int)imgA.getPixel(vecA.x, vecA.y).a > 0 && (int)imgB.getPixel(vecB.x, vecB.y).a > 0) {
					return true;
				}
			}
		}
	}

	return false;
}
