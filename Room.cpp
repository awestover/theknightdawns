
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

	bg_texture.loadFromFile("data/rooms/"+roomName+"/bg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale((TILE_WIDTH*dimensions.x)/(1.0*bg_sprite.getTextureRect().width), (TILE_WIDTH*dimensions.y)/(1.0*bg_sprite.getTextureRect().height));

	rock_texture.loadFromFile("data/imgs/rock.png");
	rock_sprite.setTexture(rock_texture);
	rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));
	
	animatedObjects["teleporter"] = new Animated(sf::Vector2i(100, 100), "data/imgs/teleporter.png");
	animatedObjects["battlePortal"] = new Animated(sf::Vector2i(100, 100), "data/imgs/battlePortal.png");
	animatedObjects["antiBattlePortal"] = new Animated(sf::Vector2i(100, 100), "data/imgs/antiBattlePortal.png");

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

void Room::draw(sf::RenderWindow *window, std::map<std::string, sf::Texture> *faces, bool battleMode){
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

	// this is WRONG WRONG WRONG: if there are multiple teleporters then it makes the animation go by way faster!!!
	// potential hacky fix: bump up the frame switch ct ;) (make it a parameter, or make a setter function)
	for(json::iterator it = objects.begin(); it!=objects.end(); ++it){
		sf::Vector2f tmp((*it)["pos"][0], (*it)["pos"][1]);
		if((*it)["type"] == "dialogue"){
			tmp = tmp*(1.0f*TILE_WIDTH);
			std::string imgName = (*it)["body"]["face"];
			sf::Texture dialogueTextureTmp = faces->at(imgName);
			dialogue_prompt_sprite.setTexture(dialogueTextureTmp);
			dialogue_prompt_sprite.setPosition(tmp);
			window->draw(dialogue_prompt_sprite);
		}
		else if((*it)["type"] == "antiBattlePortal"){
			if(!battleMode){
				animatedObjects[(*it)["type"]]->changePos(tmp.x, tmp.y);
				animatedObjects[(*it)["type"]]->draw(window);
			}
		}
		else { // types: teleporter, battlePortal
			animatedObjects[(*it)["type"]]->changePos(tmp.x, tmp.y);
			animatedObjects[(*it)["type"]]->draw(window);
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

void Room::handleObjectCollisions(Player *player, Dialogue *dialogue, HUD *hud, std::map<std::string, sf::Texture> *faces, bool *battleMode){
	for(json::iterator it = objects.begin(); it!=objects.end(); ++it){
		sf::Vector2i tmp((*it)["pos"][0], (*it)["pos"][1]);
		if(player->getTilePos() == tmp){
			if((*it)["type"] == "dialogue"){
				dialogue->setOpenState(true);
				dialogue->updateText((*it)["body"]["description"], (*it)["body"]["title"]);
				std::string imgName = (*it)["body"]["face"];
				dialogue->setSpriteTexture(&faces->at(imgName));
				player->updateQuestProgress((*it)["id"]);
			}
			else if((*it)["type"] == "teleporter"){
				sf::Vector2i newPos;
				newPos.x = (*it)["body"]["newPos"][0];
				newPos.y = (*it)["body"]["newPos"][1];
				player->teleport((*it)["body"]["newRoom"], newPos);
				hud->setRoom(player->getCurRoom());
			}
			else if((*it)["type"] == "battlePortal"){
				if(!(*battleMode)){
					sf::Vector2i newPos;
					newPos.x = (*it)["body"]["newPos"][0];
					newPos.y = (*it)["body"]["newPos"][1];
					player->teleport((*it)["body"]["newRoom"], newPos);
					hud->setRoom(player->getCurRoom());
					(*battleMode) = true;
				}
			}
			else if((*it)["type"] == "antiBattlePortal"){
				if(!(*battleMode)) {
					sf::Vector2i newPos;
					newPos.x = (*it)["body"]["newPos"][0];
					newPos.y = (*it)["body"]["newPos"][1];
					player->teleport((*it)["body"]["newRoom"], newPos);
					hud->setRoom(player->getCurRoom());
				}
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

