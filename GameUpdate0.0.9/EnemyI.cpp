#include "EnemyI.h"
EnemyI::EnemyI() {
	this->enemyIMG.loadFromFile(enemyFile);
	this->bodyIMG.loadFromFile(bodyFile);
	this->weaponIMG.loadFromFile(weaponFile);

	this->enemyTT.loadFromFile(enemyFile);
	this->bodyTT.loadFromFile(bodyFile);
	this->weaponTT.loadFromFile(weaponFile);

	this->enemySP.setTexture(enemyTT);
	this->bodySP.setTexture(bodyTT);
	this->weaponSP.setTexture(weaponTT);

	this->enemySP.setScale(scale);
	this->bodySP.setScale(scale);
	this->weaponSP.setScale(scale);

	//test hp enemy
	font.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(font);
	text.setCharacterSize(60);
	//

}

void EnemyI::_push() {
	this->enemyS.push_back(enemySP);
	this->bodyS.push_back(bodySP);
	this->weaponS.push_back(weaponSP);

	int tmpRandPos = rand() % maxLane;
	this->enemyS.back().setPosition(1700.0f, spawnPos[tmpRandPos]);
	this->bodyS.back().setPosition(1700.0f, spawnPos[tmpRandPos]);
	this->weaponS.back().setPosition(1700.0f, spawnPos[tmpRandPos]);

	this->top.push_back(0);
	std::vector<int> tmpLeft;
	for (int i = 0; i < maxTop; i++) tmpLeft.push_back(0);
	this->left.push_back(tmpLeft);

	this->mode.push_back(MOVE);
	this->side.push_back(LEFT);
	this->move.push_back(sf::Vector2f{ -speed, 0.0f });

	this->cntAtkToMove.push_back(0.0f);
	this->isEnemyDelayed.push_back(false);
	this->cntOnceDelay.push_back(0);

	// test hp enemy
	std::stringstream ss;
	ss << 100;
	this->enemyTxt.push_back(text);
	this->enemyTxt.back().setString(ss.str());
	this->enemyTxt.back().setPosition(this->enemyS.back().getPosition().x + 100, this->enemyS.back().getPosition().y - 50);
	//

	this->healthEnemyS.push_back(100);
	this->cntHitEnemyS.push_back(0);
	this->cntHitPlayer.push_back(0);
}
void EnemyI::_pop(const int index) {
	this->enemyS.erase(enemyS.begin() + index);
	this->bodyS.erase(bodyS.begin() + index);
	this->weaponS.erase(weaponS.begin() + index);

	this->top.erase(top.begin() + index);
	this->left.erase(left.begin() + index);

	this->mode.erase(mode.begin() + index);
	this->side.erase(side.begin() + index);
	this->move.erase(move.begin() + index);

	this->cntAtkToMove.erase(cntAtkToMove.begin() + index);
	this->isEnemyDelayed.erase(isEnemyDelayed.begin() + index);
	this->cntOnceDelay.erase(cntOnceDelay.begin() + index);

	//test hp enemy
	this->enemyTxt.erase(enemyTxt.begin() + index);
	//

	this->healthEnemyS.erase(healthEnemyS.begin() + index);
	this->cntHitEnemyS.erase(cntHitEnemyS.begin() + index);
	this->cntHitPlayer.erase(cntHitPlayer.begin() + index);
}

void EnemyI::setModeSideTopMove(const int mode, const int side, const int top, const sf::Vector2f move, const int index) {
	this->mode[index] = mode;
	this->side[index] = side;
	this->top[index] = top;
	this->move[index] = move;
}

void EnemyI::_setFrame(const int mode) {
	for (int i = 0; i < enemyS.size(); i++) {
		if (this->mode[i] == mode) {
			++left[i][top[i]];
			if (left[i][top[i]] >= maxLeft[top[i]]) {
				left[i][top[i]] = 0;
				if (this->mode[i] == ATK) {
					++cntOnceDelay[i];
					if (cntOnceDelay[i] == 1) {
						isEnemyDelayed[i] = true;
					}
					cntHitPlayer[i] = 0;
				}
				if (this->mode[i] == DEAD) {
					left[i][top[i]] = maxLeft[top[i]] - 1;
					indexErase.push(i);

				}
			}
		}
	}
}

void EnemyI::_setTextureRect() {
	for (int i = 0; i < enemyS.size(); i++) {
		this->enemyS[i].setTextureRect(sf::IntRect(left[i][top[i]] * imageSize.x, top[i] * imageSize.y, imageSize.x, imageSize.y));
		this->bodyS[i].setTextureRect(sf::IntRect(left[i][top[i]] * imageSize.x, top[i] * imageSize.y, imageSize.x, imageSize.y));
		this->weaponS[i].setTextureRect(sf::IntRect(left[i][top[i]] * imageSize.x, top[i] * imageSize.y, imageSize.x, imageSize.y));
	}
}
void EnemyI::_move() {
	for (int i = 0; i < enemyS.size(); i++) {
		if (move[i].x != 0) {
			this->enemyS[i].move(move[i] * this->deltaTime.asSeconds());
			this->bodyS[i].move(move[i] * this->deltaTime.asSeconds());
			this->weaponS[i].move(move[i] * this->deltaTime.asSeconds());
		}
	}
}

void EnemyI::clearEnemy() {
	while (!indexErase.empty()) {
		_pop(indexErase.top());
		indexErase.pop();
	}

	for (int i = 0; i < enemyS.size(); i++) {
		if (!isEnemyOnScreen(enemyS[i].getPosition())) indexErase.push(i);
	}

	while (!indexErase.empty()) {
		_pop(indexErase.top());
		indexErase.pop();
	}

	if (isGameOver) for (int i = 0; i < enemyS.size(); i++) _pop(i);

}
bool EnemyI::isEnemyOnScreen(sf::Vector2f enemyPos) {
	if (enemyPos.x < -70 * scale.x) {
		isHealthMiss = true;
		return false;
	}
	return true;
}
void EnemyI::onEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Numpad1)
			cntPressedNum1 = 0;
	}
}

void EnemyI::onUpdate() {
	clearEnemy();
	if (isPlayerDied && !isSetEnemyToMoveAfterPlayerDead) {
		isSetEnemyToMoveAfterPlayerDead = true;
		for (int i = 0; i < enemyS.size(); i++) {
			setModeSideTopMove(MOVE, LEFT, MOVE_L, { -speed, 0.0f }, i);
		}
	}
	if (isSlowing) {
		slowingTime.second += this->deltaTime.asSeconds();
		if (slowingTime.second >= slowingTime.first) {

			atkFrame = atkTime;
			frame = frameTime;
			speedMove = speedMoveTime;
			speed = defaultSpeed;
			isSlowing = false;

			for (int i = 0; i < enemyS.size(); i++) {
				if (mode[i] == MOVE) {
					move[i] = { -speed, 0.0f };
				}
			}
			slowingTime.second = 0.0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
		++cntPressedNum1;
		if (cntPressedNum1 == 1) {
			//spawn enemy
			_push();
		}
	}
	cntFrameTime += this->deltaTime.asSeconds();
	if (cntFrameTime >= frame) {
		_setFrame(MOVE);
		cntFrameTime = 0.0f;
	}
	cntDeadTime += this->deltaTime.asSeconds();
	if (cntDeadTime >= deadTime) {
		_setFrame(DEAD);
		cntDeadTime = 0.0f;
	}
	cntAtkTime += this->deltaTime.asSeconds();
	if (cntAtkTime >= atkFrame) {
		_setFrame(ATK);
		cntAtkTime = 0.0f;
	}
	cntSpeedMoveTime += this->deltaTime.asSeconds();
	if (cntSpeedMoveTime >= speedMove) {
		_move();
		cntSpeedMoveTime = 0.0f;
	}

	_setTextureRect();
	_move();

}
void EnemyI::_draw(sf::RenderWindow& window) {
	for (int i = 0; i < enemyS.size(); i++) {
		window.draw(enemyS[i]);
		//window.draw(bodyS[i]);
		//window.draw(weaponS[i]);

		// test hp enemy
		std::stringstream ss;
		ss << healthEnemyS[i];
		enemyTxt[i].setString(ss.str());
		enemyTxt[i].setPosition(enemyS[i].getPosition().x + 100, enemyS[i].getPosition().y - 50);
		window.draw(enemyTxt[i]);
		//
	}
}

void EnemyI::requestPlayerSprite(const sf::Sprite& playerSP) {
	this->playerSP = playerSP;
}

void EnemyI::checkSide(const int index) {
	if (enemyS[index].getPosition().x > playerSP.getPosition().x) {
		setModeSideTopMove(ATK, LEFT, ATK_L, { 0.0f, 0.0f }, index);
	}
	else if (enemyS[index].getPosition().x < playerSP.getPosition().x) {
		setModeSideTopMove(ATK, RIGHT, ATK_R, { 0.0f, 0.0f }, index);
	}
}

void EnemyI::setHealth(const std::string condition, const int index, const int curCombo) {
	if (condition == "PLAYER") {
		deltaHealthPlayer -= 11;
	}
	if (condition == "ENEMY") {
		if (curCombo == 0 || curCombo == 1) {
			healthEnemyS[index] -= 20;
			deltaScore += 20;
			energyRegen = 3;
		}
		else if (curCombo == 2 || curCombo == 3) {
			healthEnemyS[index] -= 25;
			deltaScore += 25;
			energyRegen = 5;
		}
		else if (curCombo == 4 || curCombo == 5) {
			healthEnemyS[index] -= 45;
			deltaScore += 45;
		}

		if (healthEnemyS[index] <= 0) {
			healthEnemyS[index] = 0;
			isEnemyDied = true;
			deltaScore += 20;
			if (side[index] == RIGHT) setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f }, index);
			else if (side[index] == LEFT) setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f }, index);
			energyRegen += 10;
		}
		else isEnemyDied = false;
	}
}
void EnemyI::_collision(const std::string condition, const bool isCollided, const int index, const int curCombo) {
	if (!isPlayerDied) {
		if (condition == "PLAYER V ENEMY") {
			// set Enemy to attack if condition is true else set Enemy to move
			if (isCollided) {
				checkSide(index);
			}
			else {
				if (this->isEnemyDelayed[index] == true) {

					if (cntAtkToMove[index] >= cntAtkTime) {
						setModeSideTopMove(MOVE, LEFT, MOVE_L, { -speed, 0.0f }, index);
						isEnemyDelayed[index] = false;
						cntOnceDelay[index] = 0;
						cntAtkToMove[index] = 0.0f;
					}
				}

			}
		}
	}
		if (condition == "ENEMY HIT PLAYER") {
			if (isCollided) {
				++cntHitPlayer[index];
				if (cntHitPlayer[index] == 1) {
					setHealth("PLAYER", index, curCombo);
				}
			}
			else {
				cntHitPlayer[index] = 0;
			}
		}
		if (condition == "ENEMY GOT BULLET") {
			if (isCollided) {
				setHealth("ENEMY", index, curCombo);
			}
		}	

}

short EnemyI::updateHealthPlayer() {
	short tempDeltaHealthPlayer = deltaHealthPlayer;
	deltaHealthPlayer = 0;
	return tempDeltaHealthPlayer;
}

void EnemyI::itemAffect(const int itemSelected) {
	if (itemSelected == 1) {  // slowing spell
		isSlowing = true;
		atkFrame = 0.3f;
		frame = 0.3f;
		speedMove = 0.2f;
		speed = minSpeed;

		for (int i = 0; i < enemyS.size(); i++) {
			if (mode[i] == MOVE) {
				move[i] = { -speed, 0.0f };
			}
		}
	}
	else if (itemSelected == 2) {  // lightning spell
		for (int i = 0; i < healthEnemyS.size(); i++) {
			healthEnemyS[i] -= 20;
			deltaScore += 20;
			if (healthEnemyS[i] <= 0) {
				deltaScore += 20;
				healthEnemyS[i] = 0;
				isEnemyDied = true;
				if (side[i] == RIGHT) {
					setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f }, i);
				}
				else if (side[i] == LEFT) {
					setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f }, i);
				}
			}
			else isEnemyDied = false;
		}
	}
}

short EnemyI::updateScore() {
	short tempDeltaScore = deltaScore;
	deltaScore = 0;
	return tempDeltaScore;
}

short EnemyI::updateHealthMiss() {
	if (isHealthMiss) {
		isHealthMiss = false;
		return 1;
	}
	return 0;
}

short EnemyI::updateEnergyPlayer() {
	short tempEnergyRegen = energyRegen;
	energyRegen = 0;
	return tempEnergyRegen;
}

void EnemyI::updateIsPlayerDied(const bool isPlayerDied) {
	this->isPlayerDied = isPlayerDied;
}
void EnemyI::gameOver() {
	isGameOver = true;
}