#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include"Player.h"
#include"Boss.h"
#include"EnemyI.h"
#include"EnemyII.h"
#include"EnemyIII.h"
#include"Gui.h"
#include"Item.h"

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


int main(){
	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

	sf::Vector2f mousePos;
	EnemyI* skeleton = new EnemyI;
	EnemyIII* gamma = new EnemyIII;
	EnemyII* beta = new EnemyII;
	Player* modelX = new Player;
	Boss* golaMoska = new Boss;
	Item* item = new Item;
	Gui* gui = new Gui;

	golaMoska->requestPlayerSide(modelX->side);
	golaMoska->requestPlayerScale(modelX->scale);
	

	sf::Texture t;
	sf::Sprite s;
	t.loadFromFile("Sprite/Background/dungion.png");
	s.setTexture(t);
	while (window.isOpen()) {

		skeleton->updateIsPlayerDied(modelX->isPlayerDied);
		gamma->updateIsPlayerDied(modelX->isPlayerDied);
		beta->updateIsPlayerDied(modelX->isPlayerDied);
		golaMoska->requestIsPlayerDied(modelX->isPlayerDied);

		golaMoska->requestPlayerSprite(modelX->playerSP);
		skeleton->requestPlayerSprite(modelX->playerSP);
		gamma->requestPlayerSprite(modelX->playerSP);
		beta->requestPlayerSprite(modelX->playerSP);

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
			if (!modelX->isPlayerDied) {
				modelX->onEvent(event);
				golaMoska->onEvent(event);
				skeleton->onEvent(event);
				gamma->onEvent(event);
				beta->onEvent(event);
				item->onEvent(event);
			}
			
		}

		//item selected
		short tempItemSelected = item->getItemSelected();
		item->resetItemSelected();

		if (tempItemSelected != 666) {
			if (tempItemSelected == 0 || tempItemSelected == 3) { // item for players
				modelX->itemAffect(tempItemSelected);
			}
			else if (tempItemSelected == 1 || tempItemSelected == 2) { // item for enemies
				skeleton->itemAffect(tempItemSelected);
				gui->requestScore(skeleton->updateScore());

				gamma->itemAffect(tempItemSelected);
				gui->requestScore(gamma->updateScore());

				beta->itemAffect(tempItemSelected);
				gui->requestScore(beta->updateScore());

				golaMoska->itemAffect(tempItemSelected);
				
				
			}
		}
		//

		// update health miss
		gui->requestHealthMiss(static_cast<int>(skeleton->updateHealthMiss()));
		gui->requestHealthMiss(static_cast<int>(gamma->updateHealthMiss()));
		gui->requestHealthMiss(static_cast<int>(beta->updateHealthMiss()));


		// Item collision
		if (PixelPerfectCollision(modelX->playerSP, item->itemSP, modelX->playerIMG, item->itemIMG,
			modelX->top, modelX->left[modelX->top], 0, item->currentItem, modelX->imageSize, item->imageSize)) {
			item->collision(true);
		}
		else item->collision(false);
		//


		if (!modelX->isPlayerDied) {
			if (PixelPerfectCollision(modelX->bodySP, golaMoska->weaponSP, modelX->bodyIMG, golaMoska->weaponIMG, modelX->top, modelX->left[golaMoska->top],
				golaMoska->top, golaMoska->left, modelX->imageSize, golaMoska->imageSize)) {
				// collided
				golaMoska->collision("BOSS HIT PLAYER", true, golaMoska->top);
				modelX->requestDeltaHealthPlayer(golaMoska->updateDeltaHealthPlayer());
			}
			else {
				golaMoska->collision("BOSS HIT PLAYER", false, golaMoska->top);
			}
		}
		for (int i = 0; i < modelX->bulletS.size(); i++) {
			int curVal, lastVal = -666;
			if (golaMoska->healthBoss > 0) {
				if (PixelPerfectCollision(modelX->bulletS[i], golaMoska->bodySP, modelX->bulletIMG, golaMoska->bodyIMG,
					modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], golaMoska->top, golaMoska->left,
					modelX->imageBulletSize, golaMoska->imageSize)) {
					golaMoska->collision("BOSS GOT BULLET", true, modelX->topBullet[i]);
					gui->requestScore(static_cast<short>(golaMoska->updateScore()));
					curVal = i;
					if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
					//break;
					lastVal = curVal;
				}
				else {
					golaMoska->collision("BOSS GOT BULLET", false, NULL);
				}
			}
		}
			
		//PlayerII V EnemieI
		if (!modelX->isPlayerDied) {
			for (int i = 0; i < skeleton->enemyS.size(); i++) {
				if (skeleton->healthEnemyS[i] > 0) {
					if (PixelPerfectCollision(modelX->playerSP, skeleton->enemyS[i], modelX->playerIMG, skeleton->enemyIMG,
						modelX->top, modelX->left[modelX->top], skeleton->top[i], skeleton->left[i][skeleton->top[i]],
						modelX->imageSize, skeleton->imageSize)) {
						skeleton->_collision("PLAYER V ENEMY", true, i, NULL);
					}
					else {
						skeleton->_collision("PLAYER V ENEMY", false, i, NULL);
					}

					if (PixelPerfectCollision(modelX->bodySP, skeleton->weaponS[i], modelX->bodyIMG, skeleton->weaponIMG,
						modelX->top, modelX->left[modelX->top], skeleton->top[i], skeleton->left[i][skeleton->top[i]],
						modelX->imageSize, skeleton->imageSize)) {
						skeleton->_collision("ENEMY HIT PLAYER", true, i, NULL);

						//update Health Player
						modelX->requestDeltaHealthPlayer(skeleton->updateHealthPlayer());
						gui->requestHealthPlayer(modelX->setHealthPlayer());

						//


					}
					else {
						skeleton->_collision("ENEMY HIT PLAYER", false, i, NULL);
					}
				}
			}
		}

		for (int i = 0; i < modelX->bulletS.size(); i++) {
			int curVal, lastVal = -666;
			for (int j = 0; j < skeleton->enemyS.size(); j++) {
				if (skeleton->healthEnemyS[j] > 0) {
					if (PixelPerfectCollision(modelX->bulletS[i], skeleton->bodyS[j], modelX->bulletIMG, skeleton->bodyIMG,
						modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], skeleton->top[j], skeleton->left[j][skeleton->top[j]],
						modelX->imageBulletSize, skeleton->imageSize)) {
						skeleton->_collision("ENEMY GOT BULLET", true, j, modelX->topBullet[i]);
						gui->requestScore(static_cast<short>(skeleton->updateScore()));
						curVal = i;
						if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
						//break;
						lastVal = curVal;
					}
					else {
						skeleton->_collision("ENEMY GOT BULLET", false, j, NULL);
					}
				}

			}
		}
		//-----------------------------------------------------------------------------------------------------------------
		if (!modelX->isPlayerDied) {
			for (int i = 0; i < gamma->enemyS.size(); i++) {
				if (gamma->healthEnemyS[i] > 0) {
					if (PixelPerfectCollision(modelX->playerSP, gamma->enemyS[i], modelX->playerIMG, gamma->enemyIMG,
						modelX->top, modelX->left[modelX->top], gamma->top[i], gamma->left[i][gamma->top[i]],
						modelX->imageSize, gamma->imageSize)) {
						gamma->_collision("PLAYER V ENEMY", true, i, NULL);
					}
					else {
						gamma->_collision("PLAYER V ENEMY", false, i, NULL);
					}

					if (PixelPerfectCollision(modelX->bodySP, gamma->weaponS[i], modelX->bodyIMG, gamma->weaponIMG,
						modelX->top, modelX->left[modelX->top], gamma->top[i], gamma->left[i][gamma->top[i]],
						modelX->imageSize, gamma->imageSize)) {
						gamma->_collision("ENEMY HIT PLAYER", true, i, NULL);

						//update health player
						modelX->requestDeltaHealthPlayer(gamma->updateHealthPlayer());
						gui->requestHealthPlayer(modelX->setHealthPlayer());

						//


					}
					else {
						gamma->_collision("ENEMY HIT PLAYER", false, i, NULL);
					}
				}

			}
		}

		for (int i = 0; i < modelX->bulletS.size(); i++) {
			int curVal, lastVal = -666;
			for (int j = 0; j < gamma->enemyS.size(); j++) {

				if (gamma->healthEnemyS[j] > 0) {
					if (PixelPerfectCollision(modelX->bulletS[i], gamma->bodyS[j], modelX->bulletIMG, gamma->bodyIMG,
						modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], gamma->top[j], gamma->left[j][gamma->top[j]],
						modelX->imageBulletSize, gamma->imageSize)) {
						gamma->_collision("ENEMY GOT BULLET", true, j, modelX->topBullet[i]);
						gui->requestScore(static_cast<short>(gamma->updateScore()));
						curVal = i;
						if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
						//break;
						lastVal = curVal;
					}
					else {
						gamma->_collision("GOT BULLET", false, j, NULL);
					}
				}

			}
		}

		// playerII v enemyII
		for (int i = 0; i < modelX->bulletS.size(); i++) {
			int curVal, lastVal = -666;
			for (int j = 0; j < beta->enemyS.size(); j++) {
				if (PixelPerfectCollision(modelX->bulletS[i], beta->bodyS[j], modelX->bulletIMG, beta->bodyIMG,
					modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], beta->top[j], beta->left[j][beta->top[j]],
					modelX->imageBulletSize, beta->imageSize)) {
					beta->collision("ENEMY GOT BULLET", true, j, modelX->topBullet[i]);
					gui->requestScore(static_cast<short>(beta->updateScore()));
					curVal = i;
					if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
					//break;
					lastVal = curVal;
				}
			}
		}
		if (!modelX->isPlayerDied) {
			for (int i = 0; i < beta->bulletS.size(); i++) {
				if (PixelPerfectCollision(modelX->bodySP, beta->bulletS[i], modelX->bodyIMG, beta->bulletIMG,
					modelX->top, modelX->left[modelX->top], beta->bulletTop[i], beta->bulletLeft[i],
					modelX->imageSize, beta->bulletImageSize)) {
					// collided
					beta->collision("PLAYER GOT BULLET", true, i, NULL);

					// update health player
					modelX->requestDeltaHealthPlayer(beta->updateDeltaHealthPlayer());
					gui->requestHealthPlayer(modelX->setHealthPlayer());
				}
			}
		}


		modelX->requestEnergyPlayer(gui->updateEnergyPlayer());
		gui->requestEnergyPlayer(modelX->updateEnergyPlayer());
		gui->requestEnergyPlayer(golaMoska->updateEnergyPlayer());
		gui->requestEnergyPlayer(skeleton->updateEnergyPlayer());
		gui->requestEnergyPlayer(gamma->updateEnergyPlayer());
		gui->requestEnergyPlayer(beta->updateEnergyPlayer());


		gui->requestHealthPlayer(modelX->setHealthPlayer());


		modelX->onUpdate(NULL);
		golaMoska->onUpdate();
		skeleton->onUpdate();
		gamma->onUpdate();
		beta->onUpdate();
		item->onUpdate();
		gui->onUpdate();

		window.clear(sf::Color::Magenta);
		window.draw(s);
		skeleton->_draw(window);
		gamma->_draw(window);
		beta->draw(window);
		item->_draw(window);
		gui->_draw(window);
		golaMoska->draw(window);
		modelX->_draw(window);

		window.display();

	}
	
	return 0;

}

