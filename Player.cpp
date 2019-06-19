
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

#include "Player.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

Player::Player(std::string roomName, std::string username) {
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
}

int Player::getCurrentQuestIndex(){
	int i = 0;
	// note this never infinite loops because I have a "sentinel" quest at the end of the quest list (a quest that can never be passed)
	while(quests[i]["name"]!=userData["currentQuest"]){ 
		i++;
	}
	return i;
}

std::string Player::getCurrentQuest(){
	int idx = getCurrentQuestIndex();
	return quests[idx]["name"];
}

void Player::writeUserData(){
	std::ofstream userdata_fout("data/users/"+username+".json");
	userdata_fout << userData;
}

void Player::updateQuest(){
	int i = getCurrentQuestIndex();
	// see if this can be improved...
	int tmpA = quests[i]["rewards"]["health"];
	int tmpB = userData["baseStats"]["health"];
	userData["baseStats"]["health"] = tmpA + tmpB;

	userData["currentQuest"] = quests[i+1]["name"];
	userData["questProgress"] = std::vector<bool>();
	for(json::iterator it = quests[i+1]["requirements"].begin(); it!=quests[i+1]["requirements"].end(); ++it){
		userData["questProgress"].push_back(false);
	}
	writeUserData();
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

void Player::draw(sf::RenderWindow *window) {
	sprite.setPosition(draw_pos.x - (visualDimensions.x - TILE_WIDTH), draw_pos.y - (visualDimensions.y - TILE_WIDTH));

	if(!positionsSynced()){
		int dx = TILE_WIDTH*tile_pos.x - draw_pos.x;
		int dy = TILE_WIDTH*tile_pos.y - draw_pos.y;
		if(fabs(dx) > draw_catchup_speed*0.5f){
			if(dx < 0){
				aniDirection = LEFT;
				draw_pos.x -= draw_catchup_speed;
			}
			else { // dx > 0
				aniDirection = RIGHT;
				draw_pos.x += draw_catchup_speed;
			}
		}
		else { // fabs(dy) > draw_catchup_speed*0.5f
			if(dy < 0){
				aniDirection = UP;
				draw_pos.y -= draw_catchup_speed;
			}
			else { // dy > 0
				aniDirection = DOWN;
				draw_pos.y += draw_catchup_speed;
			}
		}
	}
	else {
		aniDirection = IDLE;
	}

	aniCt += 1;
	if(aniCt == aniTurnOverCt){
		aniCt = 0;
		aniFrame = (aniFrame + 1) % numAniFrames[aniDirection];
	}

	sprite.setTextureRect(sf::IntRect(aniFrame*visualDimensions.x, aniDirection*visualDimensions.y, visualDimensions.x, visualDimensions.y));
	window->draw(sprite);
}

void Player::setPos(int xpos, int ypos){
	tile_pos.x = xpos;
	tile_pos.y = ypos;
}

sf::Vector2i Player::getTilePos(){
	return tile_pos;
}

sf::Vector2f Player::getDrawPos(){
	return draw_pos;
}

bool Player::positionsSynced(){
	bool xSynced = fabs(draw_pos.x - TILE_WIDTH*tile_pos.x) < draw_catchup_speed*0.5f;
	bool ySynced = fabs(draw_pos.y - TILE_WIDTH*tile_pos.y) < draw_catchup_speed*0.5f;
	return xSynced & ySynced;
}

std::string Player::getCurRoom(){
	return curRoom;
}

void Player::teleport(std::string newRoom, sf::Vector2i newPos){
	curRoom = newRoom;
	tile_pos.x = newPos.x; 
	tile_pos.y = newPos.y; 
	draw_pos.x = tile_pos.x*TILE_WIDTH;
	draw_pos.y = tile_pos.y*TILE_WIDTH;
}

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

int Player::getHealth(){
	return userData["baseStats"]["health"];
}

