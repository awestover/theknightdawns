
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
	bg[1] = sf::Vertex(sf::Vector2f(0, DIALOGUE_DIMENSIONS.y), sf::Color(73,104,155,150));
	bg[2] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, DIALOGUE_DIMENSIONS.y), sf::Color(54,107,193,150));
	bg[3] = sf::Vertex(sf::Vector2f(DIALOGUE_DIMENSIONS.x, 0), sf::Color(17,95,221,150));

	// i wish this where a vector of texts
	initializeText(&healthText, TEXT_PADDING*4, TEXT_PADDING*1, "Health: 10");
	initializeText(&usernameText, TEXT_PADDING*4, TEXT_PADDING*1.05+TEXT_SIZE, "Username: "+username);
	initializeText(&roomText, TEXT_PADDING*4, TEXT_PADDING*1.10+TEXT_SIZE*2, "Room: null");
	initializeText(&questText, TEXT_PADDING*4, TEXT_PADDING*1.15+TEXT_SIZE*3, "Quest: "+quest);
	std::cout <<"Quest: "+quest  << std::endl;
}

void HUD::updateHealth(int health){
	std::string tmpA("Health: ");
	std::string tmp = tmpA+std::to_string(health); 
	healthText.setString(tmp);
}

void HUD::setRoom(std::string room){
	std::string tmpA("Room: ");
	std::string tmp = tmpA+room; 
	roomText.setString(tmp);
}

void HUD::draw(sf::RenderWindow *window){
	window->setView(hudView);
	window->draw(bg, 4, sf::Quads);
	window->draw(healthText);
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

