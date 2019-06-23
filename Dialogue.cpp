
#include "Dialogue.hpp"
#include <math.h>

// Important:
// the layout of a dialogue is 
// a square DIALOGUE_DIMENSIONS.y X DIALOGUE_DIMENSIONS.y with a face in it on the far left
// and then the text
// and a close prompt it the bottom right
Dialogue::Dialogue(){
	TEXT_PADDING = 7.5f;
	TEXT_SIZE = 15;
	view.setSize(DIALOGUE_DIMENSIONS);
	view.setCenter(DIALOGUE_DIMENSIONS*0.5f);

	if(!font.loadFromFile("data/arial.ttf"))
		std::cout<<"ERROR loading arial font"<<std::endl;

	texts["dialogueTitle"] = new sf::Text;
	texts["dialogueText"] = new sf::Text;
	texts["dialogueClose"] = new sf::Text;
	initializeText(texts["dialogueTitle"], TEXT_PADDING+DIALOGUE_DIMENSIONS.y, TEXT_PADDING, "null");
	initializeText(texts["dialogueText"], TEXT_PADDING+DIALOGUE_DIMENSIONS.y, TEXT_PADDING*2+TEXT_SIZE, "null");
	initializeText(texts["dialogueClose"], 0, 0, "Press 'c' to close dialogue box"); // note: this position is fake, I set real position based on size of the text, in the next line
	texts["dialogueClose"]->setPosition(DIALOGUE_DIMENSIONS.x-texts["dialogueClose"]->getLocalBounds().width-TEXT_PADDING, DIALOGUE_DIMENSIONS.y-texts["dialogueClose"]->getLocalBounds().height-TEXT_PADDING); 

	dialogueBackdrop[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(57,74,102,150));
	dialogueBackdrop[1] = sf::Vertex(sf::Vector2f(0, DIALOGUE_DIMENSIONS.y), sf::Color(73,104,155,150));
	dialogueBackdrop[2] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, DIALOGUE_DIMENSIONS.y), sf::Color(54,107,193,150));
	dialogueBackdrop[3] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, 0), sf::Color(17,95,221,150));

}

void Dialogue::updateText(std::string newText, std::string newTitle){
	texts["dialogueText"]->setString(newText);
	texts["dialogueTitle"]->setString(newTitle);
}

void Dialogue::draw(sf::RenderWindow *window){
	window->setView(view);
	window->draw(dialogueBackdrop, 4, sf::Quads);
	window->draw(faceSprite);
	float yProposedScale = DIALOGUE_DIMENSIONS.y/(1.0*faceSprite.getTextureRect().height);
	float xProposedScale = DIALOGUE_DIMENSIONS.y/(1.0*faceSprite.getTextureRect().width);
	float actualScale = fmin(xProposedScale, yProposedScale);
	faceSprite.setScale(actualScale, actualScale);
	for(std::map<std::string, sf::Text*>::iterator it = texts.begin(); it != texts.end(); it++){
		window->draw(*(it->second));
	}
}

void Dialogue::setOpenState(bool isOpen){
	dialogueOpen = isOpen;
}

bool Dialogue::isOpen(){
	return dialogueOpen;
}

void Dialogue::setSpriteTexture(sf::Texture *texture){
	faceSprite.setTexture(*texture);
}

