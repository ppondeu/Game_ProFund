#include "Enemy.h"
Enemy::Enemy(std::string enemyFile, std::string weaponFile, std::string figureFile, std::vector<int>& maxEnemyFrame, std::vector<std::vector<int>>& hitEnemyFrame,  sf::Vector2i imageSize) {
	this->enemyFile = enemyFile;
	this->weaponFile = weaponFile;
	this->figureFile = figureFile;

	this->maxEnemyFrame = maxEnemyFrame;
	this->hitEnemyFrame = hitEnemyFrame;
	this->imageSize = imageSize;

	this->enemyIMG.loadFromFile(this->enemyFile);
	this->enemyTexture.loadFromFile(this->enemyFile);
	this->weaponIMG.loadFromFile(this->weaponFile);
	this->weaponTexture.loadFromFile(this->weaponFile);
	this->figureIMG.loadFromFile(this->figureFile);
	this->figureTexture.loadFromFile(this->figureFile);

	this->enemySprite.setTexture(this->enemyTexture);
	this->weaponSprite.setTexture(this->weaponTexture);
	this->figureSprite.setTexture(this->figureTexture);

	this->enemySprite.setTextureRect(sf::IntRect(0, 0, imageSize.x, imageSize.y));
	this->weaponSprite.setTextureRect(sf::IntRect(0, 0, imageSize.x, imageSize.y));
	this->figureSprite.setTextureRect(sf::IntRect(0,0, imageSize.x, imageSize.y));

	this->enemySprite.setScale(enemyScale);
	this->figureSprite.setScale(enemyScale);
	this->weaponSprite.setScale(enemyScale);

	font.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);

	healthDisplay = text;
	std::stringstream ss;
	ss << healthPlayer << " / " <<maxHealthPlayer;
	healthDisplay.setString(ss.str());
	healthDisplay.setOrigin(healthDisplay.getGlobalBounds().width / 2, healthDisplay.getGlobalBounds().height);
	healthDisplay.setPosition(525, 45);
	
}
void Enemy::pushEnemy() {
	this->enemies.push_back(this->enemySprite);
	this->healthEnemies.push_back(100);
	this->weaponEnemies.push_back(this->weaponSprite);
	this->figureEnemies.push_back(this->figureSprite);
	this->mode.push_back(WALK);
	this->top.push_back(0);
	this->move.push_back({ -5.0f, 0.0f });
	this->hitCounterEnemy.push_back(0);
	this->hitCounterPlayer.push_back(0);
	this->isDied.push_back(false);
	std::vector<int> tmpLeft;
	for (int i = 0; i <= maxTop;i++) {
		tmpLeft.push_back(0);
	}
	this->left.push_back(tmpLeft);
	sf::Vector2f enemiesPos = {1700.0f,  static_cast<float>(randomEnemiesPos[rand()%randomEnemiesPos.size()])};
	this->enemies.back().setPosition(enemiesPos);
	this->weaponEnemies.back().setPosition(enemiesPos);
	this->figureEnemies.back().setPosition(enemiesPos);

	enemiesText.push_back(text);
	std::stringstream ss;
	ss << 100 <<" " << mode.back();
	enemiesText.back().setString(ss.str());
	enemiesText.back().setPosition(enemiesPos.x +250, enemiesPos.y - 50);
}

void Enemy::popEnemy(int index) {
	this->enemies.erase(this->enemies.begin() + index);
	this->healthEnemies.erase(this->healthEnemies.begin() + index);
	this->weaponEnemies.erase(this->weaponEnemies.begin() + index);
	this->figureEnemies.erase(this->figureEnemies.begin() + index);
	this->mode.erase(this->mode.begin() + index);
	this->top.erase(this->top.begin() + index);
	this->left.erase(this->left.begin() + index);
	this->enemiesText.erase(this->enemiesText.begin() + index);
	this->hitCounterEnemy.erase(this->hitCounterEnemy.begin() + index);
	this->hitCounterPlayer.erase(this->hitCounterPlayer.begin() + index);
	this->isDied.erase(this->isDied.begin() + index);

	
}
void Enemy::setEnemyFrame(int mode) {
	if (mode == ATTACK) {
		for (int i = 0; i < enemies.size(); i++) {
			if (this->mode[i] == ATTACK) {
				left[i][top[i]]++;
				if (left[i][top[i]] >= maxEnemyFrame[top[i]]) {
					left[i][top[i]] = 0;
					if (this->mode[i] == ATTACK) {
						hitCounterPlayer[i] = 0;
					}
				}
			}
		}
	}
	else if (mode == WALK) {
		for (int i = 0; i < enemies.size(); i++) {
			if (this->mode[i] == WALK) {
				left[i][top[i]]++;
				if (left[i][top[i]] >= maxEnemyFrame[top[i]]) {
					left[i][top[i]] = 0;
				}
				this->enemies[i].move(move[i]);
				this->figureEnemies[i].move(move[i]);
				this->weaponEnemies[i].move(move[i]);
			}
		}
	}
	else if (mode == DEATH) {
		for (int i = 0; i < enemies.size(); i++) {
			if (this->mode[i] == DEATH) {
				left[i][top[i]]++;
				if (left[i][top[i]] >= maxEnemyFrame[top[i]]) {
					left[i][top[i]] = 0;
					this->mode[i] = DEATH;
					indexErase.push(i);

				}
			}
		}
	}

	
}
bool Enemy::isOnScreen(int posX) {
	if (posX < -150) return false;
	return true;
}
void Enemy::setInfo(int mode, int top, sf::Vector2f move, int index) {
	this->top[index] = top;
	this->mode[index] = mode;
	this->move[index] = move;
	
	this->enemies[index].setTextureRect( sf::IntRect( this->left[index][this->top[index]] * imageSize.x, this->top[index] * imageSize.y, imageSize.x, imageSize.y));
	this->weaponEnemies[index].setTextureRect(sf::IntRect(this->left[index][this->top[index]] * imageSize.x, this->top[index] * imageSize.y, imageSize.x, imageSize.y));
	this->figureEnemies[index].setTextureRect(sf::IntRect(this->left[index][this->top[index]] * imageSize.x, this->top[index] * imageSize.y, imageSize.x, imageSize.y));

}
void Enemy::resetAllFrameExceptIndex(int indexEnemy, int indexTop) {
	for (int j = 0; j < maxTop; j++) {
		if (j != indexTop) {
			left[indexEnemy][top[j]] = 0;
		}
	}
}
	

void Enemy::setHealth(int index, std::string check) {
	if (check == "PLAYER") {
		healthPlayer -= 10;
		std::stringstream ss;
		ss << healthPlayer << " / " << maxHealthPlayer;
		healthDisplay.setString(ss.str());
	}
	else if (check == "ENEMY") {
		healthEnemies[index] -= 37;
		
		if (healthEnemies[index] <= 0) {
			this->indexErase.push(index);
			//setInfo(DEATH, 2, { 0.0f, 0.0f }, index);
			//isDied[index] = true;
		}
		else {
			std::stringstream ss;
			ss << healthEnemies[index] << " " << mode[index];
			enemiesText[index].setString(ss.str());
		}
	}
		
		
	
}
void Enemy::_Collision(int index, bool isCollided, std::string check) {
	if (check == "PLAYER") {
		if (isCollided) {
			++hitCounterPlayer[index];
			if (hitCounterPlayer[index] == 1) {
				setHealth(index, check);
			}
			
		}
		else {
			hitCounterPlayer[index] = 0;
		}
	}
	else if (check == "ENEMY") {
		if (isCollided) {
			++hitCounterEnemy[index];
			if (hitCounterEnemy[index] == 1) {
				setHealth(index, check);
			}
		}
		else {
			hitCounterEnemy[index] = 0;
		}
	}
	
	
}
void Enemy::_Update(float deltaTime) {
	while (!indexErase.empty()) {
		popEnemy(indexErase.front());
		indexErase.pop();
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (!isOnScreen(enemies[i].getPosition().x)) {
			indexErase.push(i);
		}
	}
	
	while (!indexErase.empty()) {
		popEnemy(indexErase.front());

		indexErase.pop();
	}

	this->cntMoveTime += deltaTime;
	this->cntAttackTime += deltaTime;
	this->cntSpawnTime += deltaTime;
	this->cntFrameTime += deltaTime;
	this->cntDeathTime += deathTime;
	if (cntSpawnTime >= spawnTime) {
		pushEnemy();
		cntSpawnTime -= spawnTime;
	}
	/*if (cntFrameTime >= frameTime) {
		//setEnemyFrame(IDLE);
		cntFrameTime -= frameTime;
	}*/
	if (cntMoveTime >= moveTime) {
		setEnemyFrame(WALK);
		cntMoveTime -= moveTime;
	}

	if (cntAttackTime >= attackTime) {
		setEnemyFrame(ATTACK);
		cntAttackTime -= attackTime;
	}
	if (cntDeathTime >= deathTime) {
		setEnemyFrame(DEATH);
		cntDeathTime -= deathTime;
	}
	for (int i = 0; i < enemies.size(); i++) {
		setInfo(mode[i], top[i], move[i], i);
		//resetAllFrameExceptIndex(i, top[i]);
	}
	
}
void Enemy::_Draw(sf::RenderWindow& window) {
	window.draw(healthDisplay);
	for (int i = 0; i < enemies.size(); i++) {
		window.draw(enemies[i]);
		//window.draw(weaponEnemies[i]);
		//window.draw(figureEnemies[i]);
		enemiesText[i].setPosition(enemies[i].getPosition().x + 150, enemies[i].getPosition().y - 80);
		window.draw(enemiesText[i]);
	}
	
	
}

void Enemy::_Collided(std::string check, bool isCollided, int index) {
	if (isCollided) {
		if (check == "ENEMY V PLAYER") {
			setInfo(ATTACK, 1, { 0.0f, 0.0f }, index);
		}
	}
	else {
		if (check == "ENEMY V PLAYER") {
			setInfo(WALK, 0, { -5.0f, 0.0f }, index);
			hitCounterEnemy[index] = 0;
		}

	}
}