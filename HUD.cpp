
#include <iostream>

#include "HUD.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

HUD::HUD(std::string username, std::string quest) {
	hudView.setSize(HUD_DIMENSIONS);
	hudView.setCenter(HUD_DIMENSIONS*0.5f);

	if(!font.loadFromFile("data/arial.ttf"))
		std::cout<<"ERROR loading arial font"<<std::endl;

	bg[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(57,74,102,150));
	bg[1] = sf::Vertex(sf::Vector2f(0, HUD_DIMENSIONS.y), sf::Color(73,104,155,150));
	bg[2] = sf::Vertex(sf::Vector2f(HUD_DIMENSIONS.x, HUD_DIMENSIONS.y), sf::Color(54,107,193,150));
	bg[3] = sf::Vertex(sf::Vector2f(HUD_DIMENSIONS.x, 0), sf::Color(17,95,221,150));

	initializeText(&roomText, TEXT_PADDING, TEXT_PADDING, "Room: null");
	initializeText(&questText, HUD_DIMENSIONS.x/2-TEXT_PADDING*6, TEXT_PADDING, "Quest: "+quest);
	initializeText(&usernameText, 0, 0, "Username: "+username); // fake positions
	usernameText.setPosition(HUD_DIMENSIONS.x - usernameText.getLocalBounds().width-TEXT_PADDING*4, TEXT_PADDING);
}

void HUD::setRoom(std::string room){
	std::string tmpA("Room: ");
	std::string tmp = tmpA+room; 
	roomText.setString(tmp);
}

void HUD::draw(sf::RenderWindow *window){
	window->setView(hudView);
	window->draw(bg, 4, sf::Quads);
	window->draw(usernameText);
	window->draw(roomText);
	window->draw(questText);
}

void HUD::setViewport(sf::FloatRect viewport){
	hudView.setViewport(viewport);
}

void HUD::setQuest(std::string title){
	questText.setString(title);
}

void HUD::initializeText(sf::Text *text, float x, float y, std::string initString){
	text->setFont(font);
	text->setCharacterSize(TEXT_SIZE);
	text->setFillColor(sf::Color::Black);
	text->setPosition(x, y); 
	text->setString(initString);
}

