
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dialogue.hpp"
#include "constants.hpp"

void Dialogue::initialize(){
	dialogueView.setSize(DIALOGUE_DIMENSIONS);
	dialogueView.setCenter(0.5f*DIALOGUE_DIMENSIONS);

	if(!font.loadFromFile("data/arial.ttf")){
		std::cout<<"ERROR loading arial font"<<std::endl;
	}

	dialogueText.setFont(font);
	dialogueText.setCharacterSize(TEXT_SIZE);
	dialogueText.setFillColor(sf::Color::Black);
	dialogueText.setPosition(TEXT_PADDING, TEXT_PADDING); 

	dialogueClose.setFont(font);
	dialogueClose.setCharacterSize(TEXT_SIZE);
	dialogueClose.setFillColor(sf::Color::Black);
	dialogueClose.setString("Press 'c' to close dialogue box");
	dialogueClose.setPosition(DIALOGUE_DIMENSIONS.x-dialogueClose.getLocalBounds().width-TEXT_PADDING, DIALOGUE_DIMENSIONS.y-dialogueClose.getLocalBounds().height-TEXT_PADDING); 

	dialogueBackdrop[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(57,74,102));
	dialogueBackdrop[1] = sf::Vertex(sf::Vector2f(0, DIALOGUE_DIMENSIONS.y), sf::Color(73,104,155));
	dialogueBackdrop[2] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, DIALOGUE_DIMENSIONS.y), sf::Color(54,107,193));
	dialogueBackdrop[3] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, 0), sf::Color(17,95,221));

}

void Dialogue::updateText(std::string newText){
	dialogueText.setString(newText);
}

void Dialogue::draw(sf::RenderWindow *window){
	window->setView(dialogueView);
	window->draw(dialogueBackdrop, 4, sf::Quads);
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
