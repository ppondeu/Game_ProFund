#include "PlayerMovement.h"
PlayerMovement::PlayerMovement() {

	resetValue();

	flyTexture.loadFromFile("fly.png");
	flySprite.setTexture(flyTexture);
	flySprite.setScale(1.5f, 2.25f);

	idleTexture.loadFromFile(idleName[0]);
	idleSprite.setTexture(idleTexture);
	idleSprite.setPosition(playerPosition);
	idleSprite.setScale(1.5f, 2.25f);

	playerMovementSprite = idleSprite;
	playerMovementSprite.setPosition(playerPosition);

}
sf::Sprite PlayerMovement::getPlayerSprite() {
	playerMovementSprite.setPosition(playerPosition);
	return playerMovementSprite;
}
void PlayerMovement::updatePlayerMovement(sf::Vector2f playerPos) {
	playerPosition = playerPos;
	if (mode == "idle") {
		resetValue();
		++indexIdle;
		if (indexIdle >= idleName.size()) {
			indexIdle = 0;
		}
		idleTexture.loadFromFile(idleName[indexIdle]);
		idleSprite.setTexture(idleTexture);
		idleSprite.setPosition(playerPosition);
		playerMovementSprite = idleSprite;
	}
	else if (mode == "move") {
		flySprite.setPosition(playerPosition);
		playerMovementSprite = flySprite;
	}
}

void PlayerMovement::updateMoveMode(char key) {
	mode = "move";
	keyPressed = key;
	if (keyPressed == 'D') {
		++countForward;
		countBackward = 0;
		countUpward = 0;
		countDownward = 0;
		playerPosition.x += 10;
	}
	if (keyPressed == 'A') {
		++countBackward;
		countForward = 0;
		countUpward = 0;
		countDownward = 0;
		playerPosition.x -= 10;
	}
	if (keyPressed == 'S') {
		++countDownward;
		countBackward = 0;
		countUpward = 0;
		countForward = 0;
		playerPosition.y += 10;
	}
	if (keyPressed == 'W') {
		++countUpward;
		countBackward = 0;
		countForward = 0;
		countDownward = 0;
		playerPosition.y -= 10;
	}
}
void PlayerMovement::setMoveMode(char key) {
	mode = "move";
	keyPressed = key-32;
}
void PlayerMovement::resetValue() {
	mode = "idle";
	keyPressed = ' ';
	countForward = 0;
	countBackward = 0;
	countUpward = 0;
	countDownward = 0;
}