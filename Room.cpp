
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "utilityFunctions.hpp"
#include "Room.hpp"

Room::Room (std::string roomName){
	this->roomName = roomName;

	std::ifstream dimensions_fin("data/rooms/"+roomName+"/dimensions.txt");
	dimensions_fin >> dimensions.x;
	dimensions_fin >> dimensions.y;
	std::cout << dimensions.x <<" "<<dimensions.y << std::endl;

	bg_texture.loadFromFile("data/rooms/"+roomName+"/bg.png");
	bg_sprite.setTexture(bg_texture);

	rock_texture.loadFromFile("data/imgs/rock.png");
	rock_sprite.setTexture(rock_texture);
	rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));

	teleporterDimensions.x = 100; teleporterDimensions.y = 100;
	teleporter_texture.loadFromFile("data/imgs/teleporter_sheet.png");
	teleporter_sprite.setTexture(teleporter_texture);

	dialogue_prompt_texture.loadFromFile("data/imgs/dialoguePrompt.png");
	dialogue_prompt_sprite.setTexture(dialogue_prompt_texture);
	dialogue_prompt_sprite.setScale(TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().width), TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().height));

	std::ifstream obstacles_fin("data/rooms/"+roomName+"/obstacles.txt");
	obstacles = (bool**)malloc(sizeof(bool*)*dimensions.y);
	for(int i = 0; i < dimensions.y; i++){
		obstacles[i] = (bool*)malloc(sizeof(bool)*dimensions.x);
		for(int j = 0; j < dimensions.x; j++){
			char cur;
			obstacles_fin >> cur;
			obstacles[i][j] = (cur=='1');
		}
	}

	std::ifstream objects_fin("data/rooms/"+roomName+"/objects.json");
	objects_fin >> objects;

}

void Room::draw(sf::RenderWindow *window){
	window->draw(bg_sprite);

	for(int i = 0; i < dimensions.y; i++){
		for(int j = 0; j < dimensions.x; j++){
			if(obstacles[i][j]){
				const sf::Vector2f cur_pos(TILE_WIDTH*j, TILE_WIDTH*i);
				rock_sprite.setPosition(cur_pos);
				window->draw(rock_sprite);
			}
		}
	}

	teleporterAniCt += 1;
	if(teleporterAniCt == teleporterAniTurnOverCt){
		teleporterAniCt = 0;
		teleporterAniFrame = (teleporterAniFrame + 1) % teleporterNumAniFrames;
	}
	teleporter_sprite.setTextureRect(sf::IntRect(teleporterAniFrame*teleporterDimensions.x, 0, teleporterDimensions.x, teleporterDimensions.y));

	for(json::iterator it = objects.begin(); it!=objects.end(); ++it){
		sf::Vector2f tmp((*it)["pos"][0], (*it)["pos"][1]);
		tmp = tmp*(1.0f*TILE_WIDTH);
		if((*it)["type"] == "dialogue"){
			dialogue_prompt_sprite.setPosition(tmp);
			window->draw(dialogue_prompt_sprite);
		}
		else if((*it)["type"] == "teleporter") {
			tmp.x -= (teleporterDimensions.x-TILE_WIDTH)/2;
			tmp.y -= (teleporterDimensions.y-TILE_WIDTH)/2;
			teleporter_sprite.setPosition(tmp);
			window->draw(teleporter_sprite);
		}
	}
}

bool Room::collidesWithObstacles(sf::Vector2i tile_pos){
	for(int i = 0; i < dimensions.y; i++){
		for(int j = 0; j < dimensions.x; j++){
			if(obstacles[i][j]){
				if(tile_pos.x == j && tile_pos.y == i){
					return true;
				}
			}
		}
	}
	return false;
}

void Room::handleObjectCollisions(Player *player, Dialogue *dialogue, HUD *hud){
	for(json::iterator it = objects.begin(); it!=objects.end(); ++it){
		sf::Vector2i tmp((*it)["pos"][0], (*it)["pos"][1]);
		if(player->getTilePos() == tmp){
			if((*it)["type"] == "dialogue"){
				dialogue->setOpenState(true);
				dialogue->updateText((*it)["body"]["description"], (*it)["body"]["title"]);
				player->updateQuestProgress((*it)["id"]);
			}
			else if((*it)["type"] == "teleporter"){
				sf::Vector2i newPos;
				newPos.x = (*it)["body"]["newPos"][0];
				newPos.y = (*it)["body"]["newPos"][1];
				player->teleport((*it)["body"]["newRoom"], newPos);
				hud->setRoom(player->getCurRoom());
			}
		}
	}
}

std::string Room::getName(){
	return roomName;
}

sf::Vector2i Room::getDimensions(){
	return dimensions;
}

