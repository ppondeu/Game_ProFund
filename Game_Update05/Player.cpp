#include "Player.h"

Player::Player() {

	playerPosition = sf::Vector2f(400.0f, 400.0f);
	setTextureSprite();
	playerSprite.setPosition(playerPosition);

}

void Player::setPlayerSize() {

	playerSize.width = playerTexture.getSize().x / amountFrame;
	playerSize.height = playerTexture.getSize().y;
	playerSize.left = playerSize.width * indexFrame;
	playerSize.top = 0;

}

void Player::setTextureSprite() {

	playerTexture.loadFromFile(fileName);
	playerSprite.setTexture(playerTexture);
	setPlayerSize();
	playerSprite.setTextureRect(playerSize);
	playerSprite.setScale(playerScale);
	playerSprite.move(move);

}

void Player::updateValue(std::string mode, std::string side, float x, std::string fileName, int amountFrame) {

	this->mode = mode;
	this->side = side;
	move.x = x;
	this->fileName = fileName;
	this->amountFrame = amountFrame;

}

void Player::playerRender(float deltaTime) {

	totalTime += deltaTime;
	totalTime2 += deltaTime;

	++currentRun;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		if (attackState == false) {

			updateValue("move", "right", 20.0f, "Sprite/player_move_rs.png", 8);
			movedRun = currentRun;

		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		if (attackState == false) {

			updateValue("move", "left", -20.0f, "Sprite/player_move_ls.png", 8);
			movedRun = currentRun;

		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

		attackState = true;
		if (side == "right") {

			updateValue("attack", "right", 0.0f, "sprite/player_attack_1_rs.png", 9);

		}
		if (side == "left") {

			updateValue("attack", "left", 0.0f, "sprite/player_attack_2_ls.png", 7);

		}
		attackedRun = currentRun;

	}
	if (movedRun < currentRun) {

		if (mode == "move") {

			if (side == "right") {

				updateValue("idle", "right", 0.0f, "sprite/player_idle_rs.png", 4);

			}

			if (side == "left") {
				updateValue("idle", "left", 0.0f, "sprite/player_idle_rs.png", 4);
			}
		}

	}
	if (attackedRun < currentRun) {

		if (mode == "attack" && attackState == false) {

			if (side == "right") {
				updateValue("idle", "right", 0.0f, "sprite/player_idle_rs.png", 4);
			}
			if (side == "left") {
				updateValue("idle", "left", 0.0f, "sprite/player_idle_ls.png", 4);
			}

		}

	}

	if (totalTime >= switchTime) {

		if (mode == "idle") {
			++indexFrame;
			if (indexFrame >= amountFrame) indexFrame = 0;
			setTextureSprite();
		}
		totalTime -= switchTime;

	}

	if (totalTime2 >= switchTime2) {

		if (mode == "move") {

			++indexFrame;
			if (indexFrame >= amountFrame) indexFrame = 0;
			setTextureSprite();

		}
		if (mode == "attack") {

			++indexFrame;
			if (indexFrame >= amountFrame) {
				attackState = false;
				indexFrame = 0;
			}
			setTextureSprite();

		}

		totalTime2 -= switchTime2;

	}
}

void Player::playerDraw(sf::RenderWindow& window) {
	window.draw(playerSprite);
}