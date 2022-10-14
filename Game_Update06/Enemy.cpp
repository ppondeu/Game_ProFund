#include "Enemy.h"

Enemy::Enemy() {

	fileName = "sprite/enemy_walk.png";
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, enemySize.x, enemySize.y));
	sprite.setScale(sf::Vector2f(2.8, 2.8));
	enemiesPosition.x = 1838;
	enemiesPosition.y = static_cast<float>(rand() % 800);
	sprite.setPosition(enemiesPosition);
	for (int i = 0; i < maxEnemy; i++) {
		enemiesPosition.y = static_cast<float>(rand() % 800);
		sprite.setPosition(enemiesPosition);
		enemies.push_back(sprite);
		walkFrame.push_back(0);
	}

}
void Enemy::enemyRender(float deltaTime) {

	totalTime += deltaTime;
	totalTimeII += deltaTime;

	if (totalTime >= frameTime) {
		for (int i = 0; i <= enemyAmount; i++) {
			++walkFrame[i];
			if (walkFrame[i] >= maxWalkFrame) walkFrame[i] = 0;
			enemies[i].setTextureRect(sf::IntRect(enemySize.x * walkFrame[i], 0, enemySize.x, enemySize.y));
			enemies[i].move(move);
		}

		totalTime -= frameTime;
	}
	if (totalTimeII >= spawnTime) {
		if (enemyAmount < enemies.size() - 1) enemyAmount++;
		totalTimeII -= spawnTime;
	}

}

void Enemy::enemyDraw(sf::RenderWindow &window) {

	for (int i = 0; i <= enemyAmount; i++) {
		window.draw(enemies[i]);
	}

}