#include "EnemyII.h"
EnemyII::EnemyII() {

	this->enemyIMG.loadFromFile(this->enemyFile);
	this->bodyIMG.loadFromFile(this->bodyFile);
	this->bulletIMG.loadFromFile(this->bulletFile);

	this->enemyTT.loadFromFile(this->enemyFile);
	this->bodyTT.loadFromFile(this->bodyFile);
	this->bulletTT.loadFromFile(this->bulletFile);

	this->enemySP.setTexture(this->enemyTT);
	this->bodySP.setTexture(this->bodyTT);
	this->bulletSP.setTexture(this->bulletTT);
	
	font.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(font);
	text.setCharacterSize(60);
	std::stringstream ss;
	ss << 100;
	text.setString(ss.str());
	
}

void EnemyII::_push() {
	this->enemyS.push_back(enemySP);
	this->bodyS.push_back(bodySP);
	int randPos = rand() % maxLane;
	this->enemyS.back().setPosition(1700, spawnPos[randPos]);
	this->bodyS.back().setPosition(1700, spawnPos[randPos]);
	this->top.push_back(0);

	std::vector<int> tmpLeft;
	for (int i = 0; i < maxTop; i++) tmpLeft.push_back(0);
	left.push_back(tmpLeft);
	
	this->move.push_back(sf::Vector2f{ -speed * deltaTime, 0.0f });
	this->side.push_back(LEFT);
	this->mode.push_back(MOVE);

	this->cntBulletSpawnTime.push_back(0.0f);

	this->healthEnemyS.push_back(100);
	this->enemyTxt.push_back(text);
	this->enemyTxt.back().setPosition(this->enemyS.back().getPosition().x + 100, this->enemyS.back().getPosition().y - 50);
	
}
void EnemyII::_pop(const int index)
{
	this->enemyS.erase(enemyS.begin() + index);
	this->bodyS.erase(bodyS.begin() + index);
	this->top.erase(top.begin() + index);
	this->left.erase(left.begin() + index);
	this->move.erase(move.begin() + index);
	this->side.erase(side.begin() + index);
	this->mode.erase(mode.begin() + index);
	this->cntBulletSpawnTime.erase(cntBulletSpawnTime.begin() + index);
	this->healthEnemyS.erase(healthEnemyS.begin() + index);
	this->enemyTxt.erase(enemyTxt.begin() + index);

}
void EnemyII::_pushBullet(const int side, const sf::Vector2f enemyPos) {
	this->bulletS.push_back(bulletSP);
	
	if (side == LEFT) {
		this->bulletTop.push_back(1);
		this->bulletS.back().setPosition(enemyPos.x - 70, enemyPos.y + 20);
	}
	if (side == RIGHT) {
		this->bulletTop.push_back(0);
		this->bulletS.back().setPosition(enemyPos.x +200, enemyPos.y + 20);
		
	}

	std::vector<int> tmpBulletLeft;
	for (int i = 0; i < maxBulletTop; i++) tmpBulletLeft.push_back(0);
	this->bulletLeft.push_back(tmpBulletLeft);

	this->bulletSide.push_back(side);
	
}

void EnemyII::_popBullet(const int index) {
	this->bulletS.erase(bulletS.begin() + index);
	this->bulletTop.erase(bulletTop.begin() + index);
	this->bulletLeft.erase(bulletLeft.begin() + index);
	this->bulletSide.erase(bulletSide.begin() + index);
}
void EnemyII::_setTextureRect() {
	for (int i = 0; i < enemyS.size(); i++) {
		this->enemyS[i].setTextureRect(sf::IntRect(left[i][top[i]]*imageSize.x, top[i]*imageSize.y, imageSize.x, imageSize.y));
		this->bodyS[i].setTextureRect(sf::IntRect(left[i][top[i]] * imageSize.x, top[i] * imageSize.y, imageSize.x, imageSize.y));
	}
}

void EnemyII::_move() {
	for (int i = 0; i < enemyS.size(); i++) {
		if (this->mode[i] == MOVE) {
			this->enemyS[i].move(move[i]);
			this->bodyS[i].move(move[i]);
		}
		
	}
}

void EnemyII::_setFrame(const int mode) {
	for (int i = 0; i < enemyS.size(); i++) {
		if (mode == this->mode[i]) {
			++this->left[i][top[i]];
			if (left[i][top[i]] >= maxLeft[top[i]]) {
				left[i][top[i]] = 0;
					if (this->mode[i] == ATK && healthEnemyS[i] > 0) {
						setModeSideTopMove(MOVE, LEFT, MOVE_L, { -speed * deltaTime, 0.0f }, i);
					}

					if (this->mode[i] == DEAD) {
						left[i][top[i]] = maxLeft[top[i]] - 1;
						indexErase.insert(-i);
					}
				}
				
		}
	}
		
}

/*void EnemyII::_setBulletFrame() {
	for (int i = 0; i < bulletS.size(); i++) {
		++left[i][top[i]];
		if (left[i][top[i]] >= maxBulletLeft[top[i]]) {
			left[i][top[i]] = 0;
		}
	}
}*/

void EnemyII::checkSide(const int index) {

			if (enemyS[index].getPosition().x > playerSP.getPosition().x) {
				//std::cout << "LEFT ("<< enemyS[index].getPosition().x <<" > " <<playerSP.getPosition().x << std::endl;
				setModeSideTopMove(ATK, LEFT, ATK_L, { 0.0f, 0.0f }, index);
			}
			else if (enemyS[index].getPosition().x < playerSP.getPosition().x) {
				//std::cout << "RIGHT";
				setModeSideTopMove(ATK, RIGHT, ATK_R, { 0.0f, 0.0f }, index);
			}
	
}

void EnemyII::setModeSideTopMove(const int mode, const int side, const int top, const sf::Vector2f move, const int index) {
	this->mode[index] = mode;
	this->side[index] = side;
	this->top[index] = top;
	this->move[index] = move;
}

bool EnemyII::checkLane(const int index) {
		if ((playerSP.getPosition().y >= enemyS[index].getPosition().y && playerSP.getPosition().y < enemyS[index].getPosition().y + 200) || (playerSP.getPosition().y + playerSP.getGlobalBounds().height >= enemyS[index].getPosition().y && playerSP.getPosition().y + playerSP.getGlobalBounds().height < enemyS[index].getPosition().y + 200) ) {
			return true;
		}
		else return false;
}

void EnemyII::_setTextureRectBullet() {
	for (int i = 0; i < bulletS.size(); i++) {
		this->bulletS[i].setTextureRect(sf::IntRect(bulletLeft[i][bulletTop[i]] * imageBulletSize.x, bulletTop[i] * imageBulletSize.y, imageBulletSize.x, imageBulletSize.y));
		//std::cout << "eie\n";
	}
}

void EnemyII::_moveBullet() {
	for (int i = 0; i < bulletS.size(); i++) {
		
		if (this->bulletSide[i] == RIGHT) {
			bulletS[i].move(sf::Vector2f{bulletSpeed , 0.0f });
		}
		if (this->bulletSide[i] == LEFT) {
			bulletS[i].move(sf::Vector2f{ -bulletSpeed , 0.0f });
		}
	}
}
bool EnemyII::isBulletOnScreen(const sf::Vector2f bulletPos) {
	if (bulletPos.x < -90) return false;
	if (bulletPos.x > 1930) return false;
	return true;
}
void EnemyII::clearBullet() {
	for (auto it = indexBulletErase.begin() ; it != indexBulletErase.end(); it++) {
		_popBullet(-1 * *it);
	}

	if(!indexBulletErase.empty()) indexBulletErase.clear();
	for (int i = 0; i < bulletS.size(); i++) {
		if (!isBulletOnScreen(bulletS[i].getPosition())) {
			indexBulletErase.insert(-i);
		}
	}

	for (auto it = indexBulletErase.begin(); it != indexBulletErase.end(); it++) {
		_popBullet(-1 * *it);
	}
	if (!indexBulletErase.empty()) indexBulletErase.clear();
}

void EnemyII::clearEnemy() {
	for (auto it = indexErase.begin(); it != indexErase.end(); it++) {
		_pop(-1 * (*it));
	}
	indexErase.clear();
	for (int i = 0; i < enemyS.size(); i++) {
		if (!isBulletOnScreen(enemyS[i].getPosition())) {
			indexErase.insert(-i);
		}
	}

	for (auto it = indexErase.begin(); it != indexErase.end(); it++) {
		_pop(-1 * (*it));
	}
	indexErase.clear();
}
void EnemyII::onEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Numpad2) {
			cntPressedNum2 = 0;
		}
	}
}

void EnemyII::onUpdate(float deltaTime) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
		++cntPressedNum2;
		if (cntPressedNum2 == 1) {
			_push();
		}
	}
	//clearEnemy();
	//clearBullet();

	this->deltaTime = deltaTime;

	cntFrameTime += deltaTime;
	cntMoveTime += deltaTime;
	cntAtkTime += deltaTime;
	cntBulletTime += deltaTime;
	cntSpeedBulletTime += deltaTime;
	cntDeadTime += deltaTime;

	for (int i = 0; i < enemyS.size(); i++) cntBulletSpawnTime[i] += deltaTime;

	if (cntFrameTime >= frameTime) {     // set move frame
		_setFrame(MOVE);
		cntFrameTime -= frameTime;
	}
	if (cntMoveTime += deltaTime) {     // enemy move time
		_move();
		cntMoveTime -= moveTime;
	}
	if (cntAtkTime >= atkTime) {        // set enemy atk frame
		_setFrame(ATK);
		cntAtkTime -= atkTime;
	}
	if (cntBulletTime >= bulletTime) {  // set bullet frame
		//_setTextureRectBullet();
		cntBulletTime -= bulletTime;
	}
	if (cntSpeedBulletTime >= speedBulletTime) {  // bullet move time
		//_moveBullet();
		cntSpeedBulletTime -= speedBulletTime;
	}
	if (cntDeadTime >= deadTime) {
		_setFrame(DEAD);
		cntDeadTime -= deadTime;
	}

	for (int i = 0; i < enemyS.size(); i++) {
		if (cntBulletSpawnTime[i] >= bulletSpawnTime) {
			//checkLane
			if (checkLane(i)) {
				//checkSide of enemy before bullet spawning 
				checkSide(i);
				_pushBullet(side[i], enemyS[i].getPosition());
				//std::cout << "hello ";
				
			}
			cntBulletSpawnTime[i] -= bulletSpawnTime;
		}
	}

	_setTextureRect();
	//_setTextureRectBullet();
}
void EnemyII::_draw(sf::RenderWindow& window) {
	//window.draw(enemySP);
	for (int i = 0; i < enemyS.size(); i++) {
		window.draw(enemyS[i]);
		window.draw(bodyS[i]);

		std::stringstream ss;
		ss << healthEnemyS[i];
		enemyTxt[i].setString(ss.str());
		this->enemyTxt[i].setPosition(this->enemyS[i].getPosition().x + 100, this->enemyS[i].getPosition().y - 50);
		window.draw(enemyTxt[i]);
	}
	for (int i = 0; i < bulletS.size(); i++) window.draw(bulletS[i]);
}

void EnemyII::requestPlayerSprite(const sf::Sprite& playerSP) {
	this->playerSP = playerSP;
}

void EnemyII::requestHealthPlayer(const int healthPlayer) {
	this->healthPlayer = healthPlayer;
}
int EnemyII::updateHealthPlayer() {
	return healthPlayer;
}

void EnemyII::setHealth(const std::string condition, const int index) {
	if (condition == "PLAYER") {
		healthPlayer -= 30;
		//std::cout << healthPlayer << std::endl;
	}
	if (condition == "ENEMY") {
		healthEnemyS[index] -= 20;
		if (healthEnemyS[index] <= 0) {
			healthEnemyS[index] = 0;
			//std::cout << "hello";
			if (side[index] == RIGHT) {
				
				setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f }, index);
			}
			else if (side[index] == LEFT) {
				setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f }, index);
			}
		}
	}
}

void EnemyII::_collision(const std::string condition, const bool isCollided, const int index) {
	if (condition == "ENEMY GOT BULLET") {
		if (isCollided) {
			setHealth("ENEMY", index);
		}
	}
	if (condition == "PLAYER GOT BULLET") {
		if (isCollided) {
			indexBulletErase.insert(-index);
			setHealth("PLAYER", index);
		}
	}
}