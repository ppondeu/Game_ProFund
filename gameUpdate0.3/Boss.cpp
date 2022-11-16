#include "Boss.h"

Boss::Boss() {
	this->bossIMG.loadFromFile(bossFile);
	this->bodyIMG.loadFromFile(bodyFile);
	this->bulletIMG.loadFromFile(bulletFile);

	this->bossTT.loadFromFile(bossFile);
	this->bodyTT.loadFromFile(bodyFile);
	this->bulletTT.loadFromFile(bulletFile);

	this->bossSP.setTexture(bossTT);
	this->bodySP.setTexture(bodyTT);
	this->bulletSP.setTexture(bulletTT);

	this->bossSP.setScale(scale);
	this->bodySP.setScale(scale);
	this->bulletSP.setScale(scale);

	this->bossSP.setPosition(1500, 100);
	this->bodySP.setPosition(1500, 100);

	this->bossSP.setScale(sf::Vector2f(2,2));
	this->bodySP.setScale(sf::Vector2f(2, 2));

	for (int i = 0; i < maxTop; i++) left.push_back(0);

	_setTextureRect();

	for (int i = 0; i < maxWeaponTop; i++) weaponLeft.push_back(0);
}

void Boss::_setTextureRect() {
	this->bossSP.setTextureRect(sf::IntRect((imageSize.x *left[this->top]), imageSize.y * top, imageSize.x , imageSize.y));
	this->bodySP.setTextureRect(sf::IntRect((imageSize.x * left[this->top]), imageSize.y * top, imageSize.x, imageSize.y));
}

void Boss::setModeSideTopMove(int mode, int side, int top, sf::Vector2f move) {
	this->mode = mode;
	this->side = side;
	this->top = top;
	this->move = move;
}

void Boss::pushBullet() {

	float randPosX = rand() % 1700;

	while ((playerSP.getPosition().x >= randPosX && playerSP.getPosition().x <= randPosX + imageSize.x )||
		(playerSP.getPosition().x + playerSP.getGlobalBounds().width >= randPosX && playerSP.getPosition().x + playerSP.getGlobalBounds().width <= randPosX + imageSize.x)) {
		randPosX = rand() % 1700;
	}

	sf::Vector2f tmpPlayerPos = { static_cast<float>(randPosX),playerSP.getPosition().y - playerSP.getGlobalBounds().height / 2 + bossSP.getGlobalBounds().height / 2 - 170 };
	bossSP.setPosition(tmpPlayerPos);
	if (tmpPlayerPos.x < playerSP.getPosition().x) {
		setModeSideTopMove(ATK, RIGHT, ATK_R, { 0.0f, 0.0f });
	}
	else if (tmpPlayerPos.x >= playerSP.getPosition().x + playerSP.getGlobalBounds().width) {
		setModeSideTopMove(ATK, LEFT, ATK_L, { 0.0f, 0.0f });
	}

	

	isShotBullet = false;
	++cntBullet;
}
void Boss::setFrame(int mode) {
	if (mode == this->mode) {
		++left[top];
		if (left[top] >= maxLeft[top]) {
			left[top] = 0;
			if (this->mode == EXPLOSE) {
				isExploseToBullet = true;
				if (side == RIGHT) setModeSideTopMove(IDLE, side, MOVE_R, { 0.0f, 0.0f });
				else if (side == LEFT) setModeSideTopMove(IDLE, side, MOVE_L, { 0.0f, 0.0f });
			}
			if (this->mode == ATK) {
				isShotBullet = false;
				if (side == RIGHT) setModeSideTopMove(IDLE, side, MOVE_R, { 0.0f, 0.0f });
				else if (side == LEFT) setModeSideTopMove(IDLE, side, MOVE_L, { 0.0f, 0.0f });
				//std::cout << "shot bullet!\n";
				if (cntBullet >= maxBullet) {
					cntBullet = 0;
					isExploseToBullet = false;
					if (this->side == RIGHT) setModeSideTopMove(IDLE, side, MOVE_R, { 0.0f, 0.0f });
					else if (this->side == LEFT) setModeSideTopMove(IDLE, side, MOVE_L, { 0.0f, 0.0f });
					isIdleToExplose = false;
				}
			}
		}
		
	}
	
}
void Boss::_move() {
	this->bossSP.move(move);
}
void Boss::resetFrame(const int top) {
	for (int i = 0; i < maxTop; i++) {
		if (i != top) left[i] = 0;
	}
}

void Boss::onUpdate(float deltaTime) {
	cntFrameTime += deltaTime;

	if(mode == ATK) cntAtkTime += deltaTime;
	cntDeadTime += deltaTime;

	if(mode == EXPLOSE) cntExploseTime += deltaTime;

	if(!isIdleToExplose) cntIdleToExplose += deltaTime;

	if (isExploseToBullet) {
		if (!isShotBullet) cntBulletDelay += deltaTime;
	}
	//std::cout << cntBulletDelay << std::endl;
	this->deltaTime = deltaTime;
	
	if (cntFrameTime >= frameTime) {
		if (mode == IDLE) {
			setFrame(IDLE);
		}
		cntFrameTime -= frameTime;
	}
	if (cntIdleToExplose >= idleToExploseTime) {
		isIdleToExplose = true;
		if(isIdleToExplose) setModeSideTopMove(EXPLOSE, side, EXPLOSE_ATK, {0.0f, 0.0f});
		cntIdleToExplose -= idleToExploseTime;
	}

	if (cntExploseTime >= exploseTime) {
		if (this->mode == EXPLOSE) {
			setFrame(EXPLOSE);
		}
		cntExploseTime -= exploseTime;
	}

	if (cntBulletDelay >= bulletDelayTime) {
		if (isExploseToBullet) {
			isShotBullet = true;
			pushBullet();
			
		}
		cntBulletDelay -= bulletDelayTime;
	}
	if (cntAtkTime >= atkTime) {
		if (mode == ATK) {
			setFrame(ATK);
		}
		cntAtkTime -= atkTime;
	}
	if (cntDeadTime >= deadTime) {
		if (mode == DEAD) {
			setFrame(DEAD);
		}
		cntDeadTime -= deadTime;
	}
	resetFrame(top);
	_setTextureRect();
}

void Boss::_draw(sf::RenderWindow& window) {
	
	window.draw(bossSP);
}

void Boss::requestPlayerPos(sf::Vector2f playerPos) {
	this->playerPos = playerPos;
}

void Boss::requestPlayerSprite(const sf::Sprite& playerSprite) {
	this->playerSP = playerSprite;
}

void Boss::requestPlayerSide(const int playerSide) {
	this->playerSide = playerSide;
}