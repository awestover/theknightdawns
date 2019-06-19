
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dialogue.hpp"
#include "constants.hpp"

Dialogue::Dialogue(){
	dialogueView.setSize(DIALOGUE_DIMENSIONS);
	dialogueView.setCenter(DIALOGUE_DIMENSIONS*0.5f);

	if(!font.loadFromFile("data/arial.ttf"))
		std::cout<<"ERROR loading arial font"<<std::endl;

	initializeText(&dialogueTitle, TEXT_PADDING+DIALOGUE_DIMENSIONS.y, TEXT_PADDING, "null");
	initializeText(&dialogueText, TEXT_PADDING+DIALOGUE_DIMENSIONS.y, TEXT_PADDING*2+TEXT_SIZE, "null");
	initializeText(&dialogueClose, 0, 0, "Press 'c' to close dialogue box"); // note: this position is fake, I set real position based on size of the text, in the next line
	dialogueClose.setPosition(DIALOGUE_DIMENSIONS.x-dialogueClose.getLocalBounds().width-TEXT_PADDING, DIALOGUE_DIMENSIONS.y-dialogueClose.getLocalBounds().height-TEXT_PADDING); 

	dialogueBackdrop[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(57,74,102,150));
	dialogueBackdrop[1] = sf::Vertex(sf::Vector2f(0, DIALOGUE_DIMENSIONS.y), sf::Color(73,104,155,150));
	dialogueBackdrop[2] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, DIALOGUE_DIMENSIONS.y), sf::Color(54,107,193,150));
	dialogueBackdrop[3] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, 0), sf::Color(17,95,221,150));

}

void Dialogue::updateText(std::string newText, std::string newTitle){
	dialogueText.setString(newText);
	dialogueTitle.setString(newTitle);
}

void Dialogue::draw(sf::RenderWindow *window){
	window->setView(dialogueView);
	window->draw(dialogueBackdrop, 4, sf::Quads);
	window->draw(faceSprite);
	window->draw(dialogueTitle);
	window->draw(dialogueText);
	window->draw(dialogueClose);
}

void Dialogue::setDialogueViewViewport(sf::FloatRect viewport){
	dialogueView.setViewport(viewport);
}

void Dialogue::setOpenState(bool isOpen){
	dialogueOpen = isOpen;
}

bool Dialogue::isOpen(){
	return dialogueOpen;
}

void Dialogue::initializeText(sf::Text *text, float x, float y, std::string initString){
	text->setFont(font);
	text->setCharacterSize(TEXT_SIZE);
	text->setFillColor(sf::Color::Black);
	text->setPosition(x, y); 
	text->setString(initString);
}

void Dialogue::setSpriteTexture(sf::Texture *texture){
	faceSprite.setTexture(*texture);
}

