#include<SFML/Graphics.hpp>
#include<iostream>
#include"PlayerII.h"
#include"Boss.h"
#include"EnemyI.h"
#include"EnemyII.h"
#include"EnemyIII.h"
#include"Gui.h"
#include"Item.h"

bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB, int topA, int leftA, int topB, int leftB, sf::Vector2i sizeA, sf::Vector2i sizeB);

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	sf::Vector2f mousePos;
	sf::Clock clock;
	sf::Time deltaTime = sf::seconds(1.0f / 60.f);

	PlayerII modelX;
	EnemyI skeleton;
	EnemyIII gamma;
	//EnemyII beta;
	
	//Boss golaMoska;
	Item item;
	Gui gui;

	sf::Texture t;
	t.loadFromFile("Sprite/dungion.png");
	sf::Sprite s;
	s.setTexture(t);
	
	while (window.isOpen()) {

		skeleton.requestPlayerSprite(modelX.playerSP);
		gamma.requestPlayerSprite(modelX.playerSP);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
			if (event.type == sf::Event::MouseMoved) {
				mousePos.x = event.mouseMove.x;
				mousePos.y = event.mouseMove.y;
			}
			modelX.onEvent(event);
			skeleton.onEvent(event);
			gamma.onEvent(event);
			//beta.onEvent(event);
			item.onEvent(event);
		}

		//item selected
		unsigned short tempItemSelected = item.getItemSelected();
		item.resetItemSelected();

		if (tempItemSelected != 666) {
			if (tempItemSelected == 0 || tempItemSelected == 3) { // item for players
				modelX.itemAffect(tempItemSelected);
			}
			else if (tempItemSelected == 1 || tempItemSelected == 2) { // item for enemies
				skeleton.itemAffect(tempItemSelected);
				gamma.itemAffect(tempItemSelected);
			}
		}
		//

		// update health miss
		gui.requestHealthMiss(static_cast<int>(skeleton.updateHealthMiss()));
		gui.requestHealthMiss(static_cast<int>(gamma.updateHealthMiss()));

		// Item collision
		if (PixelPerfectCollision(modelX.playerSP, item.itemSP, modelX.playerIMG, item.itemIMG,
			modelX.top, modelX.left[modelX.top], 0, item.currentItem, modelX.imageSize, item.imageSize)) {
			item.collision(true);
			//std::cout << "collided ";
		}
		else item.collision(false);
		//

		//PlayerII V Enemies
		//{
			//skeleton.requestHealthPlayer(healthPlayer);
			if (!modelX.isPlayerDied) {
				for (int i = 0; i < skeleton.enemyS.size(); i++) {
					if (skeleton.healthEnemyS[i] > 0) {
						if (PixelPerfectCollision(modelX.playerSP, skeleton.enemyS[i], modelX.playerIMG, skeleton.enemyIMG,
							modelX.top, modelX.left[modelX.top], skeleton.top[i], skeleton.left[i][skeleton.top[i]],
							modelX.imageSize, skeleton.imageSize)) {
							skeleton._collision("PLAYER V ENEMY", true, i, NULL);
						}
						else {
							skeleton._collision("PLAYER V ENEMY", false, i, NULL);
						}

						if (PixelPerfectCollision(modelX.bodySP, skeleton.weaponS[i], modelX.bodyIMG, skeleton.weaponIMG,
							modelX.top, modelX.left[modelX.top], skeleton.top[i], skeleton.left[i][skeleton.top[i]],
							modelX.imageSize, skeleton.imageSize)) {
							skeleton._collision("ENEMY HIT PLAYER", true, i, NULL);

							//updateHealth Player
							modelX.requestDeltaHealthPlayer(skeleton.updateHealthPlayer());
							skeleton.requestHealthPlayer(modelX.setHealthPlayer());
							gamma.requestHealthPlayer(modelX.setHealthPlayer());
							gui.requestHealthPlayer(modelX.setHealthPlayer());
							//
							

						}
						else {
							skeleton._collision("ENEMY HIT PLAYER", false, i, NULL);
						}
					}
				}
			}

			for (int i = 0; i < modelX.bulletS.size(); i++) {
				int curVal, lastVal = -666;
				for (int j = 0; j < skeleton.enemyS.size(); j++) {
					if (skeleton.healthEnemyS[j] > 0) {
						if (PixelPerfectCollision(modelX.bulletS[i], skeleton.bodyS[j], modelX.bulletIMG, skeleton.bodyIMG,
							modelX.topBullet[i], modelX.leftBullet[i][modelX.topBullet[i]], skeleton.top[j], skeleton.left[j][skeleton.top[j]],
							modelX.imageBulletSize, skeleton.imageSize)) {
							skeleton._collision("ENEMY GOT BULLET", true, j, modelX.topBullet[i]);
							gui.requestScore(static_cast<unsigned>(skeleton.updateScore()));
							curVal = i;
							if (curVal != lastVal) modelX._collision("ENEMY GOT BULLET", true, i);
							//break;
							lastVal = curVal;
						}
						else {
							skeleton._collision("ENEMY GOT BULLET", false, j, NULL);
						}
					}
					
				}
			}
			//-----------------------------------------------------------------------------------------------------------------
			if (!modelX.isPlayerDied) {
				for (int i = 0; i < gamma.enemyS.size(); i++) {

					if (gamma.healthEnemyS[i] > 0) {
						if (PixelPerfectCollision(modelX.playerSP, gamma.enemyS[i], modelX.playerIMG, gamma.enemyIMG,
							modelX.top, modelX.left[modelX.top], gamma.top[i], gamma.left[i][gamma.top[i]],
							modelX.imageSize, gamma.imageSize)) {
							gamma._collision("PLAYER V ENEMY", true, i, NULL);
						}
						else {
							gamma._collision("PLAYER V ENEMY", false, i, NULL);
						}

						if (PixelPerfectCollision(modelX.bodySP, gamma.weaponS[i], modelX.bodyIMG, gamma.weaponIMG,
							modelX.top, modelX.left[modelX.top], gamma.top[i], gamma.left[i][gamma.top[i]],
							modelX.imageSize, gamma.imageSize)) {
							gamma._collision("ENEMY HIT PLAYER", true, i, NULL);
							
							//update health player
							modelX.requestDeltaHealthPlayer(gamma.updateHealthPlayer());
							skeleton.requestHealthPlayer(modelX.setHealthPlayer());
							gamma.requestHealthPlayer(modelX.setHealthPlayer());
							gui.requestHealthPlayer(modelX.setHealthPlayer());
							//
							

						}
						else {
							gamma._collision("ENEMY HIT PLAYER", false, i, NULL);
						}
					}

				}
			}

			for (int i = 0; i < modelX.bulletS.size(); i++) {
				int curVal, lastVal = -666;
				for (int j = 0; j < gamma.enemyS.size(); j++) {

					if (gamma.healthEnemyS[j] > 0) {
						if (PixelPerfectCollision(modelX.bulletS[i], gamma.bodyS[j], modelX.bulletIMG, gamma.bodyIMG,
							modelX.topBullet[i], modelX.leftBullet[i][modelX.topBullet[i]], gamma.top[j], gamma.left[j][gamma.top[j]],
							modelX.imageBulletSize, gamma.imageSize)) {
							gamma._collision("ENEMY GOT BULLET", true, j, modelX.topBullet[i]);
							gui.requestScore(static_cast<unsigned>(gamma.updateScore()));
							curVal = i;
							if (curVal != lastVal) modelX._collision("ENEMY GOT BULLET", true, i);
							//break;
							lastVal = curVal;
						}
						else {
							gamma._collision("GOT BULLET", false, j, NULL);
						}
					}

				}
			}

		modelX.requestEnergyPlayer(gui.updateEnergyPlayer());
		gui.requestEnergyPlayer(modelX.updateEnergyPlayer());
		gui.requestEnergyPlayer(skeleton.updateEnergyPlayer());
		gui.requestEnergyPlayer(gamma.updateEnergyPlayer());


		gui.requestHealthPlayer(modelX.setHealthPlayer());
		skeleton.requestHealthPlayer(modelX.setHealthPlayer());
		gamma.requestHealthPlayer(modelX.setHealthPlayer());

		modelX.onUpdate(deltaTime.asSeconds());
		skeleton.onUpdate();
		gamma.onUpdate();
		item.onUpdate();
		gui.onUpdate();

		window.clear(sf::Color::Magenta);

		window.draw(s);
		skeleton._draw(window);
		gamma._draw(window);
		item._draw(window);
		gui._draw(window);
		modelX._draw(window);
		
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
