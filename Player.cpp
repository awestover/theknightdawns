
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

#include "Player.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

Player::Player(std::string roomName, std::string username) {
	numAniFrames = new int[9] {6,6,5,5,4,3,3,3,3};
	visualDimensions.x = 84; visualDimensions.y = 84;
	curRoom = roomName;
	tile_pos.x = 1; tile_pos.y = 1;
	draw_pos.x = tile_pos.x*TILE_WIDTH; draw_pos.y = tile_pos.y*TILE_WIDTH; 
	texture.loadFromFile("data/imgs/knight.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,visualDimensions.x,visualDimensions.y));
	this->username = username;

	std::ifstream userdata_fin("data/users/"+username+".json");
	userdata_fin >> userData;

	std::ifstream quests_fin("data/quests.json");
	quests_fin >> quests;

	health = userData["baseStats"]["health"];
}

// other

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

void Player::handleEnemyCollisions(Enemy *enemy){
	// weird thing: what if positions aren't synced!!! 
	// temporary solution: don't care about it
	if (enemy->getTilePos().x == tile_pos.x && enemy->getTilePos().y == tile_pos.y){
		this->handleAttack(enemy->getAttack());
		enemy->handleAttack(this->getAttack());
	}

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

