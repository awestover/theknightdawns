
#include <iostream>

#include "HUD.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

HUD::HUD(std::string username, std::string quest) {
	view.setSize(HUD_DIMENSIONS);
	view.setCenter(HUD_DIMENSIONS*0.5f);

	if(!font.loadFromFile("data/arial.ttf"))
		std::cout<<"ERROR loading arial font"<<std::endl;

	bg[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(57,74,102,150));
	bg[1] = sf::Vertex(sf::Vector2f(0, HUD_DIMENSIONS.y), sf::Color(73,104,155,150));
	bg[2] = sf::Vertex(sf::Vector2f(HUD_DIMENSIONS.x, HUD_DIMENSIONS.y), sf::Color(54,107,193,150));
	bg[3] = sf::Vertex(sf::Vector2f(HUD_DIMENSIONS.x, 0), sf::Color(17,95,221,150));

	texts["roomText"] = new sf::Text;
	texts["questText"] = new sf::Text;
	texts["usernameText"] = new sf::Text;
	initializeText(texts["roomText"], TEXT_PADDING, TEXT_PADDING, "Room: null");
	initializeText(texts["questText"], HUD_DIMENSIONS.x/2-TEXT_PADDING*6, TEXT_PADDING, "Quest: "+quest);
	initializeText(texts["usernameText"], 0, 0, "Username: "+username); // fake positions
	texts["usernameText"]->setPosition(HUD_DIMENSIONS.x - texts["usernameText"]->getLocalBounds().width-TEXT_PADDING*4, TEXT_PADDING);
}

void HUD::setRoom(std::string room){
	std::string tmpA("Room: ");
	std::string tmp = tmpA+room; 
	texts["roomText"]->setString(tmp);
}

void HUD::draw(sf::RenderWindow *window){
	window->setView(view);
	window->draw(bg, 4, sf::Quads);
	for(std::map<std::string, sf::Text*>::iterator it = texts.begin(); it != texts.end(); it++){
		window->draw(*(it->second));
	}
}

void HUD::setQuest(std::string title){
	texts["questText"]->setString(title);
}

