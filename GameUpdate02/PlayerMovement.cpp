#include "PlayerMovement.h"
PlayerMovement::PlayerMovement(std::string fileName) {
	indexDefault = 0;
	Mode = "default";
	flyTexture.loadFromFile(fileName);
	flySprite.setTexture(flyTexture);
	flySprite.setPosition(PlayerMovementPosition);
	flySprite.setScale(1*1.5f, static_cast<float>(flyTexture.getSize().y)/ static_cast<float>(flyTexture.getSize().x)*1.5f);
	
	defaultTexture.loadFromFile(playerMovementFilename[0]);
	defaultSprite.setTexture(defaultTexture);
	defaultSprite.setPosition(PlayerMovementPosition);
	defaultSprite.setScale(1 * 1.5f, static_cast<float>(flyTexture.getSize().y) / static_cast<float>(flyTexture.getSize().x) * 1.5f);

	tmpSprite = defaultSprite;

}

void PlayerMovement::updateDefault() {
	PlayerMovementPosition = tmpSprite.getPosition();
	++indexDefault;
	if (indexDefault >= playerMovementFilename.size()) {
		indexDefault = 0;
	}
	defaultTexture.loadFromFile(playerMovementFilename[indexDefault]);
	defaultSprite.setTexture(defaultTexture);
	defaultSprite.setPosition(PlayerMovementPosition);
	tmpSprite = defaultSprite;
}
void PlayerMovement::updateFly(char KeyPressed) {
	PlayerMovementPosition = tmpSprite.getPosition();
	if (KeyPressed == 'D') {
		PlayerMovementPosition.x += 10;
	}
	if (KeyPressed == 'A') {
		PlayerMovementPosition.x -= 10;
	}
	if (KeyPressed == 'W') {
		PlayerMovementPosition.y -= 10;
	}
	if (KeyPressed == 'S') {
		PlayerMovementPosition.y += 10;
	}
	flySprite.setPosition(PlayerMovementPosition);
	tmpSprite = flySprite;
}

void PlayerMovement::updatePlayerPosition(std::string mode) {
	PlayerMovementPosition = tmpSprite.getPosition();
	if (mode == "fly") {
		flySprite.setPosition(PlayerMovementPosition);
		tmpSprite = flySprite;
	}
	if (mode == "default") {
		defaultSprite.setPosition(PlayerMovementPosition);
		tmpSprite = defaultSprite;
	}
}
sf::Sprite PlayerMovement::getFlySprite() {
	return flySprite;
}
sf::Sprite PlayerMovement::getDefaultSprite() {
	return defaultSprite;
}
sf::Sprite PlayerMovement::getTempSprite() {
	return tmpSprite;
}