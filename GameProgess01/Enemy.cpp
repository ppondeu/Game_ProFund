#include "Enemy.h"

Enemy::Enemy() {
	filename = "Sprite/enemy_walk.png";
	enemyTexture.loadFromFile(filename);
	imageSize = sf::Vector2i(enemyTexture.getSize().x / maxWalkFrame, enemyTexture.getSize().y);
	countImage = sf::Vector2i(0, 0);
	enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(sf::Vector2f(2.5, 2.5));
	enemySprite.setPosition(sf::Vector2f(1700.0f, static_cast<float>(rand() % 900)));

}

void Enemy::pushbackEnemy() {
	++countEnemy;
	if (countEnemy <= maxEnemySpawn) {
		indexFrame.push_back(0);
		enemies.push_back(enemySprite);
		enemyPosition = sf::Vector2f(1700.0f, static_cast<float>(rand() % 900));
		enemies.back().setPosition(enemyPosition);
	}


}

void Enemy::setEnemy() {
	for (int i = 0; i < enemies.size(); i++) {
		++indexFrame.at(i);
		if (indexFrame.at(i) >= maxWalkFrame) indexFrame.at(i) = 0;
		enemies.at(i).setTextureRect(sf::IntRect(imageSize.x * indexFrame.at(i), 0, imageSize.x, imageSize.y));
		enemies.at(i).move(move);
	}
}

bool Enemy::isOnTheScreen(int enemyPositionX) {
	if (enemyPositionX < -82) return false;
	else return true;
}
void Enemy::enemyRender(float deltaTime) {
	totalTimeI += deltaTime;
	totalTimeII += deltaTime;

	for (int i = 0; i < enemies.size(); i++) {
		if (!isOnTheScreen(enemies.at(i).getPosition().x)) {
			enemies.erase(enemies.begin() + i);
			indexFrame.erase(indexFrame.begin() + i);
		}
	}

	if (totalTimeI >= frameTime) {
		setEnemy();
		totalTimeI -= frameTime;
	}
	if (totalTimeII >= spawnTime) {
		pushbackEnemy();
		totalTimeII -= spawnTime;
	}

}

void Enemy::enemyDraw(sf::RenderWindow& window) {

	for (int i = 0; i < enemies.size(); i++) {
		window.draw(enemies.at(i));
	}

}