
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

#include "Player.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

Player::Player(std::string roomName, std::string username) {
	projectile.setProjectileRechargeFrames(30);
	numAniFrames = new int[9] {6,6,5,5,4,3,3,3,3};
	visualDimensions.x = 84; visualDimensions.y = 84;
	curRoom = roomName;
	changePos(1, 1);
	texture.loadFromFile("data/imgs/knight.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,visualDimensions.x,visualDimensions.y));
	this->username = username;

	std::ifstream userdata_fin("data/users/"+username+".json");
	userdata_fin >> userData;

	std::ifstream quests_fin("data/quests.json");
	quests_fin >> quests;

	health = userData["baseStats"]["health"];

	arrowTexture.loadFromFile("data/imgs/arrow.png");
	arrowSprite.setTexture(arrowTexture);
}

// other

void Player::drawArrow(sf::RenderWindow *window){
	sf::Vector2i sus(0,0);
	sf::Vector2f arrowDirrection = dijkstra.getOptimalPath(getTilePos(), getCurRoom(), sus, "nextRoom");
	std::cout << arrowDirrection.x << " " << arrowDirrection.y << std::endl;
	arrowSprite.setPosition(-arrowDims/2, -arrowDims/2);
	sf::Transform rotateToPoint(arrowDirrection.x, -arrowDirrection.y, 0,
								arrowDirrection.y, arrowDirrection.x, 0, 
									0, 0, 1);
	int r = visualDimensions.x;
	sf::Transform moveToPos(1,0,draw_pos.x+visualDimensions.x/2+arrowDirrection.x*r,
							0,1,draw_pos.y+visualDimensions.y/2+arrowDirrection.y*r,
							0,0,1);

	window->draw(arrowSprite, moveToPos*rotateToPoint);
}

void Player::writeUserData(){
	std::ofstream userdata_fout("data/users/"+username+".json");
	userdata_fout << userData;
}

void Player::teleport(std::string newRoom, sf::Vector2i newPos){
	curRoom = newRoom;
	tile_pos.x = newPos.x; 
	tile_pos.y = newPos.y; 
	draw_pos.x = tile_pos.x*TILE_WIDTH;
	draw_pos.y = tile_pos.y*TILE_WIDTH;
}

// misc quest stuff

void Player::updateQuestProgress(std::string id){
	int j = getCurrentQuestIndex();
	for(int i = 0; i < quests[j]["requirements"].size(); i++){
		if(quests[j]["requirements"][i]["room"] == curRoom && quests[j]["requirements"][i]["id"] == id){
			userData["questProgress"][i] = true;
			writeUserData();
			if(questCompleted()){
				updateQuest();
			}
			break;
		}	
	}
}

bool Player::questCompleted(){	
	for(json::iterator it = userData["questProgress"].begin(); it!=userData["questProgress"].end(); ++it){
		int tmp = *it;
		if(!tmp){
			return false;
		}
	}
	return true;
}

void Player::updateQuest(){
	int i = getCurrentQuestIndex();
	// see if this can be improved...
	int newHealth = quests[i]["rewards"]["health"];
	int oldHealth = userData["baseStats"]["health"];
	userData["baseStats"]["health"] = newHealth + oldHealth;
	health += newHealth;

	userData["currentQuest"] = quests[i+1]["name"];
	userData["questProgress"] = std::vector<bool>();
	for(json::iterator it = quests[i+1]["requirements"].begin(); it!=quests[i+1]["requirements"].end(); ++it){
		userData["questProgress"].push_back(false);
	}
	writeUserData();
}

// getters
std::string Player::getCurRoom(){
	return curRoom;
}

std::string Player::getCurrentQuest(){
	int idx = getCurrentQuestIndex();
	return quests[idx]["name"];
}

int Player::getCurrentQuestIndex(){
	int i = 0;
	// note this never infinite loops because I have a "sentinel" quest at the end of the quest list (a quest that can never be passed)
	while(quests[i]["name"]!=userData["currentQuest"]){ 
		i++;
	}
	return i;
}

