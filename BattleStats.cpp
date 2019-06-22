
#include <iostream>

#include "BattleStats.hpp"
#include "constants.hpp"

BattleStats::BattleStats(){
	view.setSize(BATTLE_STATS_DIMENSIONS);
	view.setCenter(BATTLE_STATS_DIMENSIONS*0.5f);

	if(!font.loadFromFile("data/arial.ttf"))
		std::cout<<"ERROR loading arial font"<<std::endl;

	texts["playerHealth"] = new sf::Text;
	texts["playerAttack"] = new sf::Text;
	texts["enemyHealth"] = new sf::Text;
	texts["enemyAttack"] = new sf::Text;
	initializeText(texts["playerHealth"], BATTLE_STATS_DIMENSIONS.y, 0, "Health: 0");
	initializeText(texts["playerAttack"], BATTLE_STATS_DIMENSIONS.y, TEXT_SIZE, "Attack: 0");
	initializeText(texts["enemyHealth"], BATTLE_STATS_DIMENSIONS.x/2+BATTLE_STATS_DIMENSIONS.y, 0, "Health: 0");
	initializeText(texts["enemyAttack"], BATTLE_STATS_DIMENSIONS.x/2+BATTLE_STATS_DIMENSIONS.y, TEXT_SIZE, "Attack: 0");

	battleStatsBackdrop[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(57,74,102,150));
	battleStatsBackdrop[1] = sf::Vertex(sf::Vector2f(0, BATTLE_STATS_DIMENSIONS.y), sf::Color(73,104,155,150));
	battleStatsBackdrop[2] = sf::Vertex(sf::Vector2f(BATTLE_STATS_DIMENSIONS.x, BATTLE_STATS_DIMENSIONS.y), sf::Color(54,107,193,150));
	battleStatsBackdrop[3] = sf::Vertex(sf::Vector2f(BATTLE_STATS_DIMENSIONS.x, 0), sf::Color(17,95,221,150));

}

void BattleStats::draw(sf::RenderWindow *window){
	window->setView(view);
	window->draw(battleStatsBackdrop, 4, sf::Quads);
	window->draw(playerFace);
	window->draw(enemyFace);
	for(std::map<std::string, sf::Text*>::iterator it = texts.begin(); it != texts.end(); it++){
		window->draw(*(it->second));
	}
}

void BattleStats::setPlayerFaceTexture(sf::Texture *texture){
	playerFace.setPosition(0,0);
	playerFace.setTexture(*texture);
}

void BattleStats::setEnemyFaceTexture(sf::Texture *texture){
	enemyFace.setPosition(BATTLE_STATS_DIMENSIONS.x/2,0);
	enemyFace.setTexture(*texture);
}

