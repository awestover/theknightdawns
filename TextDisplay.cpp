
#include "TextDisplay.hpp"

void TextDisplay::initializeText(sf::Text *text, float x, float y, std::string initString){
	text->setFont(font);
	text->setCharacterSize(TEXT_SIZE);
	text->setFillColor(sf::Color::Black);
	text->setPosition(x, y); 
	text->setString(initString);
}

void TextDisplay::setViewport(sf::FloatRect viewport){
	view.setViewport(viewport);
}

