#include "Boss.h"

Boss::Boss() {
	this->bossIMG.loadFromFile(bossFile);
	this->bodyIMG.loadFromFile(bodyFile);
	this->weaponIMG.loadFromFile(weaponFile);

	this->bossTT.loadFromFile(bossFile);
	this->bodyTT.loadFromFile(bodyFile);
	this->weaponTT.loadFromFile(weaponFile);

	this->bossSP.setTexture(bossTT);
	this->bodySP.setTexture(bodyTT);
	this->weaponSP.setTexture(weaponTT);

	this->bossSP.setScale(scale);
	this->bodySP.setScale(scale);
	this->weaponSP.setScale(scale);

	this->bossSP.setPosition(1500, 400);
	this->bodySP.setPosition(1500, 400);
	this->weaponSP.setPosition(1500, 400);
	
	setTextureRect();

	font.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Yellow);
	text.setString("Chasing...");
	text.setPosition(500, 20);
	
}

void Boss::setModeSideTopMove(const short mode, const short side, const short top, const sf::Vector2f move) {
	this->mode = mode;
	this->side = side;
	this->top = top;
	this->move = move;
}
void Boss::setTextureRect() {
	this->bossSP.setTextureRect(sf::IntRect(left * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->bodySP.setTextureRect(sf::IntRect(left * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->weaponSP.setTextureRect(sf::IntRect(left * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
}

void Boss::bossMove() {
	this->bodySP.move(move * deltaTime.asSeconds());
	this->bossSP.move(move * deltaTime.asSeconds());
	this->weaponSP.move(move * deltaTime.asSeconds());
}
void Boss::setFrame(const short mode) {
	if (this->mode == mode) {
		++left;
		if (left >= maxLeft[top]) {
			left = 0;
			if (this->mode == ATK) {
				setModeSideTopMove(EXP, side, EXPLOSE, { 0.0f, 0.0f });
				cntIsAttack = 0;
				cntHitPlayer = 0;
			}
			else if (this->mode == EXP) {
				if (side == RIGHT) setModeSideTopMove(MOVE, side, MOVE_R, {speed, move.y});
				else if (side == LEFT) setModeSideTopMove(MOVE, side, MOVE_L, { -speed, move.y });
			}
		}
	}
	
}

void Boss::chasing() {
	if (side == LEFT) {
		if (bossSP.getPosition().x + 35 * scale.x > playerSP.getPosition().x + (38 + 36) * playerScale.x) {
			setModeSideTopMove(mode, LEFT, MOVE_L, move);
		}
		else if (bossSP.getPosition().x + (35 + 73) * scale.x < playerSP.getPosition().x + 38 * playerScale.x) {
			setModeSideTopMove(mode, RIGHT, MOVE_R, move);
		}
	}
	else if (side == RIGHT) {
		if (bossSP.getPosition().x + 65 * scale.x > playerSP.getPosition().x + (38 + 36) * playerScale.x) {
			setModeSideTopMove(mode, LEFT, MOVE_L, move);
		}
		if (bossSP.getPosition().x + (65 + 73) * scale.x < playerSP.getPosition().x + (38 + 36) * playerScale.x) {
			setModeSideTopMove(mode, RIGHT, MOVE_R, move);
		}
	}

	if (side == LEFT) {
		setModeSideTopMove(mode, side, top, {-speed, move.y});
		if (bossSP.getPosition().x + 35 * scale.x < playerSP.getPosition().x + (38+36)*playerScale.x + 10) {
			setModeSideTopMove(mode, side, top, { 0, move.y });
		}

	}
	else if (side == RIGHT) {
		setModeSideTopMove(mode, side, top, { speed, move.y });
		if (bossSP.getPosition().x + (65 + 73) * scale.x > playerSP.getPosition().x + (38) * playerScale.x - 10) {
			setModeSideTopMove(mode, side, top, { 0, move.y });
		}
	}

	if (side == LEFT) {
		if (playerSP.getPosition().x + (38 + 36) * playerScale.x > bossSP.getPosition().x + (35) * scale.x &&
			playerSP.getPosition().x + (38 + 36) * playerScale.x < bossSP.getPosition().x + (65 + 73) * scale.x) {
			setModeSideTopMove(mode, side, top, { speed, move.y });
		}
	}
	else if (side == RIGHT) {
		if (playerSP.getPosition().x + 38 * playerScale.x > bossSP.getPosition().x + 35 * scale.x &&
			playerSP.getPosition().x + 38 * playerScale.x < bossSP.getPosition().x + (65 + 73) * scale.x) {
			setModeSideTopMove(mode, side, top, { -speed, move.y });
		}
	}

	if (bossSP.getPosition().y  + 64 * scale.y < playerSP.getPosition().y + 8 * playerScale.y -20) {
		setModeSideTopMove(mode, side, top, { move.x, speed });
	}
	else if (bossSP.getPosition().y + 64 * scale.y > playerSP.getPosition().y + 8 * playerScale.y + 20) {
		setModeSideTopMove(mode, side, top, { move.x, -speed });
	}
	else {
		setModeSideTopMove(mode, side, top, { move.x, 0.0f});
	}
	/*if (bossSP.getPosition().y > playerSP.getPosition().y - 20 && bossSP.getPosition().y < playerSP.getPosition().y + 20) {
		move.y = 0;
	}*/

	if (move.x == 0 && move.y == 0) {
		++cntIsAttack;
		if (cntIsAttack) {
			isAttack = true;
			if (side == RIGHT) setModeSideTopMove(ATK, side, ATK_R, { 0.0f, 0.0f });
			else if (side == LEFT) setModeSideTopMove(ATK, side, ATK_L, { 0.0f, 0.0f });
		}
		
		text.setString("READY TO ATTACK");
	}
	else text.setString("Chasing...");

}
void Boss::onEvent(const sf::Event& event) {
	
}

void Boss::onUpdate() {
	if(mode != EXP && mode != ATK) chasing();

	if (mode == MOVE) {
		
		cntMoveFrame += deltaTime.asSeconds();
		if (cntMoveFrame >= curMoveFrame) {
			setFrame(MOVE);
			cntMoveFrame -= curMoveFrame;
		}
	}
	else if (mode == ATK) {
		cntAtkFrame += deltaTime.asSeconds();
		if (cntAtkFrame >= curAtkFrameTime) {
			setFrame(ATK);
			cntAtkFrame -= curAtkFrameTime;
		}
	}
	else if (mode == EXP) {
		cntExpFrame += deltaTime.asSeconds();
		if (cntExpFrame >= curExpFrameTime) {
			setFrame(EXP);
			cntExpFrame -= curExpFrameTime;
		}
	}
	else if (mode == DEAD) {
		cntDead += deltaTime.asSeconds();
		if (cntDead >= deadFrameTime) {
			setFrame(DEAD);
			cntDead -= deadFrameTime;
		}
	}
	setTextureRect();
	bossMove();
	
}

void Boss::draw(sf::RenderWindow& window) {
	window.draw(bossSP);
	window.draw(bodySP);
	window.draw(weaponSP);

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(imageSize));
	rect.setOutlineThickness(-1);
	rect.setOutlineColor(sf::Color::Blue);
	rect.scale(scale);
	if (side == LEFT) rect.setPosition(bossSP.getPosition().x + (35 * scale.x), bossSP.getPosition().y + 62 * scale.y);
	else if (side == RIGHT) rect.setPosition(bossSP.getPosition().x + (65 * scale.x), bossSP.getPosition().y + 62 * scale.y);

	rect.setSize(sf::Vector2f(73, 87));
	rect.setFillColor(sf::Color::Transparent);
	window.draw(rect);
	
	window.draw(text);
}

void Boss::setHealth(const std::string condition, const short curCombo) {
	if (condition == "PLAYER") {
		if (curCombo == 2 || curCombo == 3) deltaHealthPlayer -= 79;
		else if (curCombo == 4) deltaHealthPlayer -= 1;
	}
	if (condition == "ENEMY") {
		if (curCombo == 0 || curCombo == 1) {
			healthBoss -= 20;
			energyRegen += 3;
		}
		else if (curCombo == 2 || curCombo == 3) {
			healthBoss -= 25;
			energyRegen += 5;
		}
		else if (curCombo == 4 || curCombo == 5) {
			healthBoss -= 45;
		}

		if (healthBoss <= 0) {
			healthBoss = 0;
			isBossDied = true;
			if (side == RIGHT) setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f });
			else if (side == LEFT) setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f });
			energyRegen += 10;
		}
		else isBossDied = false;
	}
}

void Boss::collision(const std::string condition, const bool isCollided, const short curCombo) {
	if (condition == "BOSS HIT PLAYER") {
		if (isCollided) {
			++cntHitPlayer;
			if (curCombo == 2 || curCombo == 3) {
				if (cntHitPlayer == 1) {
					setHealth("PLAYER", curCombo);
				}
			}
			else if (curCombo == 4) setHealth("PLAYER", curCombo);
		}
		else {
			cntHitPlayer = 0;
		}
	}
	else if (condition == "BOSS GOT BULLET") {
		if (isCollided) {
			setHealth("BOSS", curCombo);
		}
	}

}

void Boss::requestPlayerSprite(const sf::Sprite& playerSP) {
	this->playerSP = playerSP;
}

void Boss::requestPlayerSide(const short playerSide) {
	this->playerSide = playerSide;
}

void Boss::requestPlayerScale(const sf::Vector2f& playerScale) {
	this->playerScale = playerScale;
}

short Boss::updateDeltaHealthPlayer() {
	short tempDeltaHealthPlayer = deltaHealthPlayer;
	deltaHealthPlayer = 0;
	return tempDeltaHealthPlayer;
}

short Boss::updateEnergyPlayer() {
	short tempEnergyRegen = energyRegen;
	energyRegen = 0;
	return tempEnergyRegen;
}

void Boss::requestIsPlayerDied(const bool isPlayerDied) {
	this->isPlayerDied = isPlayerDied;
}


