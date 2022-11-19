#include "Gui.h"
Gui::Gui() {
	this->maxHealthPlayer = healthPlayer;
	this->font.loadFromFile(this->fontFile);

	this->hpMissTT.loadFromFile(this->hpMissFile);
	this->outerBarTT.loadFromFile(this->outerBarFile);
	this->innerHpBarTT.loadFromFile(this->innerHpBarFile);
	this->innerEnergyBarTT.loadFromFile(this->innerEnergyBarFile);
	this->hpIconTT.loadFromFile(this->hpIconFile);
	this->energyIconTT.loadFromFile(this->energyIconFile);


	this->hpMissSP.setTexture(hpMissTT);
	this->outerHpBarSP.setTexture(outerBarTT);
	this->innerHpBarSP.setTexture(innerHpBarTT);
	this->outerEnergyBarSP.setTexture(outerBarTT);
	this->innerEnergyBarSP.setTexture(innerEnergyBarTT);
	this->hpIconSP.setTexture(hpIconTT);
	this->energyIconSP.setTexture(energyIconTT);

	this->hpMissTxt.setFont(font);
	this->hpBarTxt.setFont(font);
	this->energyBarTxt.setFont(font);
	this->scoreTxt.setFont(font);

	this->hpMissTxt.setCharacterSize(40);
	this->hpBarTxt.setCharacterSize(40);
	this->energyBarTxt.setCharacterSize(40);
	this->scoreTxt.setCharacterSize(40);

	this->hpMissSP.setOrigin(hpMissSP.getGlobalBounds().width / 2, hpMissSP.getGlobalBounds().height / 2);
	this->outerHpBarSP.setOrigin(outerHpBarSP.getGlobalBounds().width / 2, outerHpBarSP.getGlobalBounds().height / 2);
	this->innerHpBarSP.setOrigin(innerHpBarSP.getGlobalBounds().width / 2, innerHpBarSP.getGlobalBounds().height / 2);
	this->outerEnergyBarSP.setOrigin(outerEnergyBarSP.getGlobalBounds().width / 2, outerEnergyBarSP.getGlobalBounds().height / 2);
	this->innerEnergyBarSP.setOrigin(innerEnergyBarSP.getGlobalBounds().width / 2, innerEnergyBarSP.getGlobalBounds().height / 2);
	this->hpIconSP.setOrigin(hpIconSP.getGlobalBounds().width / 2, hpIconSP.getGlobalBounds().height / 2);
	this->energyIconSP.setOrigin(energyIconSP.getGlobalBounds().width / 2, energyIconSP.getGlobalBounds().height / 2);

	this->hpMissSP.setPosition(45, 175);
	this->outerHpBarSP.setPosition(300, 45);
	this->innerHpBarSP.setPosition(300, 45);
	this->outerEnergyBarSP.setPosition(300, 110);
	this->innerEnergyBarSP.setPosition(300, 110);
	this->hpIconSP.setPosition(45, 45);
	this->energyIconSP.setPosition(45, 110);

	this->hpMissTxt.setOrigin(hpMissTxt.getGlobalBounds().width / 2, hpMissTxt.getGlobalBounds().height / 2);
	this->hpBarTxt.setOrigin(hpBarTxt.getGlobalBounds().width / 2, hpBarTxt.getGlobalBounds().height / 2);
	this->energyBarTxt.setOrigin(energyBarTxt.getGlobalBounds().width / 2, energyBarTxt.getGlobalBounds().height / 2);
	this->scoreTxt.setOrigin(scoreTxt.getGlobalBounds().width / 2, scoreTxt.getGlobalBounds().height / 2);

	this->hpMissTxt.setPosition(80, 145);
	this->hpBarTxt.setPosition(230, 20);
	this->energyBarTxt.setPosition(230, 80);
	this->scoreTxt.setPosition(1570,30);

	scoreTxt.setFillColor(sf::Color::Yellow);

	onUpdate();

}

void Gui::onUpdate() {
	
	ss << "X" << healthMiss;
	this->hpMissTxt.setString(ss.str());
	ss.str("");
	ss << healthPlayer << "/" << maxHealthPlayer;
	this->hpBarTxt.setString(ss.str());
	ss.str("");
	ss << energyPlayer << "/" << maxEnergyPlayer;
	this->energyBarTxt.setString(ss.str());
	ss.str("");
	ss << "SCORE : " << score;
	this->scoreTxt.setString(ss.str());
	ss.str("");

	cntRegen += deltaTime.asSeconds();

	if (energyPlayer < 0) energyPlayer = 0;
	this->innerEnergyBarSP.setTextureRect(sf::IntRect(0, 0, energyPlayer * 4, 40));
	if (healthPlayer < 0) healthPlayer = 0;
	this->innerHpBarSP.setTextureRect(sf::IntRect(0, 0, healthPlayer / 1.75, 40));
	if (cntRegen >= regenTime) {
		energyPlayer += 2;
		if (energyPlayer > 100) energyPlayer = 100;
		cntRegen -= regenTime;
	}
}
void Gui::_draw(sf::RenderWindow& window) {
	
	window.draw(hpMissSP);
	window.draw(hpMissTxt);
	window.draw(hpIconSP);
	window.draw(energyIconSP);
	window.draw(outerHpBarSP);
	window.draw(innerHpBarSP);
	window.draw(hpBarTxt);
	window.draw(outerEnergyBarSP);
	window.draw(innerEnergyBarSP);
	window.draw(energyBarTxt);
	window.draw(scoreTxt);

}

void Gui::requestEnergyPlayer(const short energyPlayer) {
	this->energyPlayer += energyPlayer;
	if (this->energyPlayer <= 0) this->energyPlayer = 0;
	if (this->energyPlayer > 100) this->energyPlayer = 100;
}

void Gui::requestHealthPlayer(const short healthPlayer) {
	this->healthPlayer = healthPlayer;
	if (this->healthPlayer <= 0) this->healthPlayer = 0;
	if (this->healthPlayer > this->maxHealthPlayer) this->healthPlayer = this->maxHealthPlayer;
}

void Gui::requestScore(const short deltaScore) {
	this->score += deltaScore;
}

void Gui::requestHealthMiss(const int healthMiss) {
	this->healthMiss -= healthMiss;
	if (this->healthMiss <= 0) {
		this->healthMiss = 0;
		//statement
	}
}

int Gui::updateEnergyPlayer() {
	return energyPlayer;
}