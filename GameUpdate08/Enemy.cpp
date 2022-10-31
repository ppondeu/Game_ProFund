#include "Enemy.h"
#include<sstream>
Enemy::Enemy() {
	filename = "Sprite/enemy_walk.png";
	imgEnemy.loadFromFile(filename);
	enemyTexture.loadFromFile(filename);
	imageSize = sf::Vector2i(enemyTexture.getSize().x / maxWalkFrame, enemyTexture.getSize().y);
	//countImage = sf::Vector2i(0, 0);
	enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(sf::Vector2f(2.62, 2.62));
	//enemySprite.setPosition(sf::Vector2f(1700.0f, static_cast<float>(rand() % 900)));

	font.loadFromFile("Font/PixelFont2.ttf");
	
	this->tmpText.setFont(font);
	this->tmpText.setFillColor(sf::Color::Green);
	//this->tmpText.setScale(5, 5);
	this->tmpText.setCharacterSize(60);
	//this->tmpText.setPosition(100, 100);
	

}
/*
Enemy::Enemy(std::string enemyFile, std::vector<int>& enemyFrame) {
	this->enemyFrame = enemyFrame;
	filename = enemyFile;
	imgEnemy.loadFromFile(filename);
	enemyTexture.loadFromFile(filename);
	imageSize = sf::Vector2i(enemyTexture.getSize().x / maxWalkFrame, enemyTexture.getSize().y);
	//countImage = sf::Vector2i(0, 0);
	enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(sf::Vector2f(2.62, 2.62));
	//enemySprite.setPosition(sf::Vector2f(1700.0f, static_cast<float>(rand() % 900)));

	font.loadFromFile("Font/PixelFont2.ttf");

	this->tmpText.setFont(font);
	this->tmpText.setFillColor(sf::Color::Green);
	this->tmpText.setCharacterSize(60);
}*/

void Enemy::pushbackEnemy() {
	++countEnemy;
	if (countEnemy <= maxEnemySpawn) {
		indexFrame.push_back(0);
		health.push_back(100);
		hitCounter.push_back(0);
		damageRecieved.push_back(0);
		enemies.push_back(enemySprite);
		t.push_back(tmpText);

		enemyPosition = sf::Vector2f(1920.0f, randPos.at(rand()%randPos.size()));
		enemies.back().setPosition(enemyPosition);

	}


}

void Enemy::setEnemy() {
	for (int i = 0; i < enemies.size(); i++) {
		++indexFrame.at(i);
		if (indexFrame.at(i) >= maxWalkFrame) {
			indexFrame.at(i) = 0;
			//hitCounter.at(i) = 0;
		}
		enemies.at(i).setTextureRect(sf::IntRect(imageSize.x * indexFrame.at(i), 0, imageSize.x, imageSize.y));//imageSize.y * top.at(i)
		enemies.at(i).move(move);
		
	}
}

/*void Enemy::enemyStance(int index, std::string mode) {
	if (mode == "walk"){
		top.at(index) = 0;
	}
	else if (mode == "attack") {
		top.at(index) = 1;
	}
	else if (mode == "death") {
		top.at(index) = 2;
	}
}*/
bool Enemy::isOnScreen(int enemyPositionX) {
	if (enemyPositionX < -100) return false;
	else return true;
}
void Enemy::eraseEnemy(int index) {
	enemies.erase(enemies.begin() + index);
	indexFrame.erase(indexFrame.begin() + index);
	health.erase(health.begin() + index);
	hitCounter.erase(hitCounter.begin() + index);
	damageRecieved.erase(damageRecieved.begin() + index);
	t.erase(t.begin() + index);
}
void Enemy::collision(int index, bool isCollide, int currentStance, int indexFrame) {
	if (isCollide) {
		++hitCounter.at(index);
		if (hitCounter.at(index) == 1) {
			health.at(index) -= 100;
			if (health.at(index) <= 0) {
				eraseEnemy(index);
			}
		}
	}
	else {
		hitCounter.at(index) = 0;
	}
	
}
void Enemy::enemyRender(float deltaTime) {
	totalTimeI += deltaTime;
	totalTimeII += deltaTime;

	for (int i = 0; i < enemies.size(); i++) {
		if (!isOnScreen(enemies.at(i).getPosition().x)) {
			eraseEnemy(i);
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
		std::stringstream ss;
		ss << health.at(i);
		t.at(i).setString(ss.str());
		t.at(i).setPosition(enemies.at(i).getPosition().x + 70, enemies.at(i).getPosition().y - 70);
		window.draw(t.at(i));
	}
	/*std::stringstream ss;
	if (!enemies.empty()) {
		ss << health.at(0);
		tmpText.setString(ss.str());
		window.draw(tmpText);
	}*/


}