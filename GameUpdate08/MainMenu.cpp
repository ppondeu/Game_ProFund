#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window, sf::String stringText, sf::Color colorText , unsigned characterSize, float positionX, float positionY) {
	screenSize = sf::Vector2f(window.getSize());
	this->stringText = stringText;
	this->characterSize = characterSize;
	this->colorText = colorText;
	this->positionY = positionY;
	this->positinX = positionY;
	positionText = sf::Vector2f(positionX, positionY);
	init();
}
MainMenu::MainMenu(sf::RenderWindow& window, sf::String stringText, unsigned index, sf::Color colorText, unsigned characterSize) {
	screenSize = sf::Vector2f(window.getSize());
	this->stringText = stringText;
	this->index = index;
	this->colorText = colorText;
	this->characterSize = characterSize;
	initText();
}
void MainMenu::init() {
	fontText.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(fontText);
	text.setCharacterSize(characterSize);
	text.setString(stringText);
	text.setFillColor(colorText);
	originText = sf::Vector2f(text.getLocalBounds().width / 2,
		text.getLocalBounds().height / 2);
	text.setOrigin(originText);
	text.setPosition(positionText);
}
void MainMenu::initText() {
	fontText.loadFromFile("Font/PixelFont2.ttf");
	text.setFont(fontText);
	text.setCharacterSize(characterSize);
	text.setString(stringText);
	text.setFillColor(colorText);
	originText = sf::Vector2f(text.getLocalBounds().width / 2,
		text.getLocalBounds().height / 2);
	text.setOrigin(originText);
	positionText = sf::Vector2f(screenSize.x / 2, 190 +(200 * index));
	text.setPosition(positionText);
}

void MainMenu::switchColor(sf::Vector2f mousePosition) {
	if (text.getGlobalBounds().contains(mousePosition)) text.setFillColor(sf::Color::Red);
	else text.setFillColor(sf::Color::White);
}

bool MainMenu::mouseButtonPressedState(sf::Vector2f mousePosition, bool boolean) {
	if (text.getGlobalBounds().contains(mousePosition)) return !boolean;
	else return boolean;
}
void MainMenu::mainMenuDraw(sf::RenderWindow& window) {
	window.draw(text);
}