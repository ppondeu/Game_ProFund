#include "Player.h"
Player::Player(std::string playerFile, std::string weaponFile, std::string figureFile, std::vector<int>& maxPlayerFrame, 
	std::vector<std::vector<int>>& hitPlayerFrame, sf::Vector2i imageSize) {
	this->playerFile = playerFile;
	this->weaponFile = weaponFile;
	this->figureFile = figureFile;

	this->maxPlayerFrame = maxPlayerFrame;
	this->hitPlayerFrame = hitPlayerFrame;
	this->imageSize = imageSize;

	this->playerIMG.loadFromFile(this->playerFile);
	this->playerTexture.loadFromFile(this->playerFile);
	this->weaponIMG.loadFromFile(this->weaponFile);
	this->weaponTexture.loadFromFile(this->weaponFile);
	this->figureIMG.loadFromFile(this->figureFile);
	this->figureTexture.loadFromFile(this->figureFile);

	this->playerSprite.setTexture(this->playerTexture);
	this->weaponSprite.setTexture(this->weaponTexture);
	this->figureSprite.setTexture(this->figureTexture);

	for (int i = 0; i <= maxTop; i++) {
		left.push_back(0);
	}

	this->playerSprite.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->weaponSprite.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->figureSprite.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));

	this->playerSprite.setScale(playerScale);
	this->weaponSprite.setScale(playerScale);
	this->figureSprite.setScale(playerScale);

	this->playerSprite.setPosition(500.0f, 500.0f);
	this->weaponSprite.setPosition(500.0f, 500.0f);
	this->figureSprite.setPosition(500.0f, 500.0f);

}
void Player::resetAllFrameExceptIndex(int index) {
	for (int i = 0; i < maxTop; i++) {
		if (i != index) {
			left[i] = 0;
		}
	}
}
void Player::setInfo(int mode, int side, int top, sf::Vector2f move) {
	this->mode = mode;
	this->side = side;
	this->top = top;
	this->move = move;

	this->playerSprite.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->weaponSprite.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->figureSprite.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));

	this->playerSprite.move(this->move);
	this->weaponSprite.move(this->move);
	this->figureSprite.move(this->move);

}
void Player::_OnEvent(sf::RenderWindow& window, sf::Event& evnt) {
	sf::Event event = evnt;
	if (event.type == event.KeyPressed ) {
		if (event.key.code == sf::Keyboard::J){
			cntComboTime = 0.0f;
			++cntPressed;
			if (cntPressed == 1){
				isAttack = true;
				if (side == RIGHT){
					setInfo(ATTACK, RIGHT, comboDefault[comboRun], {0.0f, 0.0f});
						//resetAllFrameExceptIndex(top);
				}
				else if (side == LEFT) {
					setInfo(ATTACK, LEFT, comboDefault[comboRun]+1, {0.0f, 0.0f});
						//resetAllFrameExceptIndex(top);
				}
			}
			
		}
	}
	if (event.type == event.KeyReleased) {
		
		if (!isAttack ) {
			if (event.key.code == sf::Keyboard::D) {
				setInfo(IDLE, RIGHT, 0, { 0.0f, 0.0f });
				//resetAllFrameExceptIndex(top);
			}
			if (event.key.code == sf::Keyboard::A) {
				setInfo(IDLE, LEFT, 1, { 0.0f, 0.0f });
				//resetAllFrameExceptIndex(top);
			}
			if (event.key.code == sf::Keyboard::W) {
				if (side == RIGHT) {
					setInfo(IDLE, RIGHT, 0, { 0.0f, 0.0f });
					//resetAllFrameExceptIndex(top);
				}
				else if (side == LEFT) {
					setInfo(IDLE, LEFT, 1, { 0.0f, 0.0f });
					//resetAllFrameExceptIndex(top);
				}

			}
			if (event.key.code == sf::Keyboard::S) {
				if (side == RIGHT) {
					setInfo(IDLE, RIGHT, 0, { 0.0f, 0.0f });
					//resetAllFrameExceptIndex(top);
				}
				else if (side == LEFT) {
					setInfo(IDLE, LEFT, 1, { 0.0f, 0.0f });
					//resetAllFrameExceptIndex(top);
				}
			}
		}
		if (event.key.code == sf::Keyboard::J) {
			cntPressed = 0;
		}
	}
}

void Player::_Update(float deltaTime, sf::Vector2i& mousePos) {
	this->mousePos = mousePos;
	cntIdleTime += deltaTime;
	cntMoveTime += deltaTime;
	cntAttackTime += deltaTime;
	cntComboTime += deltaTime;
	if (!isAttack) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			setInfo(MOVE, RIGHT, 2, { 10.0f, 0.0f });
			//resetAllFrameExceptIndex(top);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			setInfo(MOVE, LEFT, 3, { -10.0f, 0.0f });
			//resetAllFrameExceptIndex(top);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (side == RIGHT) {
				setInfo(MOVE, RIGHT, 4, { 0.0f, -7.0f });
				//resetAllFrameExceptIndex(top);
			}
			else if (side == LEFT) {
				setInfo(MOVE, LEFT, 5, { 0.0f, -7.0f });
				//resetAllFrameExceptIndex(top);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (side == RIGHT) {
				setInfo(MOVE, RIGHT, 4, { 0.0f, 7.0f });
				//resetAllFrameExceptIndex(top);
			}
			else if (side == LEFT) {
				setInfo(MOVE, LEFT, 5, { 0.0f, 7.0f });
				//resetAllFrameExceptIndex(top);
			}
		}
	}

	if (cntIdleTime >= idleTime) {
		if (mode == IDLE && !isAttack ) {
			++left[top];
			if (left[top] >= maxPlayerFrame[top]) left[top] = 0;
		}
		
		cntIdleTime -= idleTime;
	}

	if (cntMoveTime >= moveTime) {
		if (mode == MOVE && !isAttack) {
			++left[top];
			if (left[top] >= maxPlayerFrame[top]) left[top] = 0;
		}
		if (mode == DEATH) {
			++left[top];
			if (left[top] >= maxPlayerFrame[top]) {
				left[top] = 0;
				std::cout << "YOU LOSS";
				deltaTime = 0;
				
			}
		}

		cntMoveTime -= moveTime;
	}

	if (cntAttackTime >= attackTime) {
		if (mode == ATTACK && isAttack) {
			left[top]++;
			if (left[top] >= maxPlayerFrame[top]) {
				left[top] = 0;
				isAttack = false;
				if (side == RIGHT) {
					setInfo(IDLE, RIGHT, 0, { 0.0f, 0.0f });
					////resetAllFrameExceptIndex(top);
				}
				else if (side == LEFT) {
					setInfo(IDLE, LEFT, 1, { 0.0f, 0.0f });
					////resetAllFrameExceptIndex(top);
				}
				if (cntComboTime < comboTime) {
					++comboRun;
					if (comboRun >= comboDefault.size()) comboRun = 0;
				}
				
			}
			
		}
		cntAttackTime -= attackTime;
	}
	if(cntComboTime >= comboTime) {
		comboRun = 0;
	}
	
	setInfo(this->mode, this->side, this->top, this->move);
}
void Player::_Draw(sf::RenderWindow& window) {
	//window.draw(weaponSprite);
	//window.draw(figureSprite);
	window.draw(playerSprite);
	//window.draw(text);
}