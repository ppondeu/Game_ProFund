#include "Player.h"

Player::Player(std::string filename, std::vector<int> &maxFrame) {
	this->filename = filename;
	this->maxFrame = maxFrame;
	this->imgPlayer.loadFromFile(filename);
	playerTexture.loadFromFile(filename);
	playerSprite.setTexture(playerTexture);
	imageSize = sf::Vector2i{ static_cast<int>(playerTexture.getSize().x / 11), static_cast<int>(playerTexture.getSize().y / 18) };
	setRowColumn(sf::Vector2i{0,0});
	
	for (int i = 0; i < 18; i++) {
		indexFrame.push_back(0);
	}
	playerSprite.setScale(2.2f, 2.2f);
	playerSprite.setPosition(0.0f, 270.0f);
}

void Player::setRowColumn(sf::Vector2i countImage) {
	playerSprite.setTextureRect(sf::IntRect(countImage ,imageSize));
}
void Player::setFrame() {
	playerSprite.setTextureRect(sf::IntRect( imageSize.x * indexFrame[currentStance], imageSize.y * currentStance, imageSize.x, imageSize.y));
	
}
void Player::playerEvent(std::string eventType, std::string key) {
	this->eventType = eventType;
	this->key = key;
}
void Player::resetStance() {
	mode = "idle";
	eventType = "N/A";
	key = "N/A";
	if (side == "right") {
		currentStance = 0;
	}
	else if (side == "left") {
		currentStance = 1;
	}
}
void Player::playerRender(float deltaTime) {
	totalTime += deltaTime;
	totalTimeII += deltaTime;
	if (eventType == "KeyPressed") {
		if (key == "K") {
			attackNo = 1;
			++countPressed;
			if (countPressed == 1) {
				isAttack = true;
				mode = "attack";
				if (countUltimateStance == 0) {
					if (side == "right") {
						currentStance = 12;
					}
					else if (side == "left") {
						currentStance = 13;
					}
				}
				else {
					if (side == "right") {
						currentStance = 14;
					}
					else if (side == "left") {
						currentStance = 15;
					}
				}
				
			}
		}
		if (key == "L") {
			attackNo = 0;
			++countPressed;
			if (countPressed == 1) {
				attackNo = 0;
				isAttack = true;
				mode = "attack";
				if (countAttackStance%3 == 0) {
					if (side == "right") {
						currentStance = 6;
					}
					else if (side == "left") {
						currentStance = 7;
					}
				}
				else if(countAttackStance%3==1) {
					if (side == "right") {
						currentStance = 8;
					}
					else if (side == "left") {
						currentStance = 9;
					}
				}
				else if (countAttackStance % 3 == 2) {
					if (side == "right") {
						currentStance = 10;
					}
					else if (side == "left") {
						currentStance = 11;
					}
				}

			}
		}

	}
	if (eventType == "KeyReleased") {
		if (key == "L"){
			countPressed = 0;
		}
		if (key == "D") {
			resetStance();
		}
		if (key == "A") {
			resetStance();
		}
		if (key == "W") {
			resetStance();
		}
		if (key == "S") {
			resetStance();
		}
		if (key == "K") {
			countPressed = 0;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mode = "move";
		side = "right";
		move = sf::Vector2f{ 10.0f, 0 };
		currentStance = 2;
		playerSprite.move(move);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		mode = "move";
		side = "left";
		move = sf::Vector2f{ -10.0f, 0 };
		currentStance = 3;
		playerSprite.move(move);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		mode = "move";
		if (side == "right") currentStance = 4;
		else if (side == "left") currentStance = 5;
		move = sf::Vector2f{ 0, -10.0f };
		playerSprite.move(move);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		mode = "move";
		move = sf::Vector2f{ 0, 10.0f };
		if (side == "right") currentStance = 4;
		else if (side == "left") currentStance = 5;
		playerSprite.move(move);
	}

	if (totalTime >= frameTime) {
		if (mode == "idle") {
			for (int i = 0; i < 18;i++) {
				if (currentStance == i) {
					++indexFrame[i];
					if (indexFrame[i] >= maxFrame[i]) {
						indexFrame[i] = 0;
					}
				}
				else {
					indexFrame[i] = 0;
				}
			}
		}
		totalTime -= frameTime;
	}
	if (totalTimeII >= moveTime) {
		if (mode == "move") {
			for (int i = 0; i < 18; i++) {
				if (currentStance == i) {
					++indexFrame[i];
					if (indexFrame[i] >= maxFrame[i]) {
						indexFrame[i] = 0;
					}
				}
				else {
					indexFrame[i] = 0;
				}
			}
		}
		if (mode == "attack" ) {
			if (attackNo == 1) {
				for (int i = 0; i < 18; i++) {
					if (currentStance == i) {
						++indexFrame[i];
						if (indexFrame[i] >= maxFrame[i]) {
							indexFrame[i] = 0;
							isAttack = false;
							countUltimateStance = !countUltimateStance;
							resetStance();

						}
					}
					else {
						indexFrame[i] = 0;
					}
				}
			}
			else if (attackNo == 0) {
				for (int i = 0; i < 18; i++) {
					if (currentStance == i) {
						++indexFrame[i];
						if (indexFrame[i] >= maxFrame[i]) {
							indexFrame[i] = 0;
							isAttack = false;
							++countAttackStance;
							resetStance();

						}
					}
					else {
						indexFrame[i] = 0;
					}
				}
			}
			
		}
		totalTimeII -= moveTime;
	}
	setFrame();
	
}

void Player::playerDraw(sf::RenderWindow &window) {
	window.draw(playerSprite);
}
