
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "utilityFunctions.hpp"
#include "Room.hpp"

Room::Room (std::string roomName){
	this->roomName = roomName;

	// this should probably be room specific...
	bg_texture.loadFromFile("data/imgs/tileMap.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setTextureRect(sf::IntRect(0, 0, WOLRD_DIMENSIONS.x, WOLRD_DIMENSIONS.y)); // seems sketchy....

	rock_texture.loadFromFile("data/imgs/rock.png");
	rock_sprite.setTexture(rock_texture);
	rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));

	teleporter_texture.loadFromFile("data/imgs/teleporter.png");
	teleporter_sprite.setTexture(teleporter_texture);
	teleporter_sprite.setScale(TILE_WIDTH/(1.0*teleporter_sprite.getTextureRect().width), TILE_WIDTH/(1.0*teleporter_sprite.getTextureRect().height));

	dialogue_prompt_texture.loadFromFile("data/imgs/dialoguePrompt.png");
	dialogue_prompt_sprite.setTexture(dialogue_prompt_texture);
	dialogue_prompt_sprite.setScale(TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().width), TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().height));

	std::ifstream obstacles_fin("data/rooms/"+roomName+"/obstacles.txt");
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			char cur;
			obstacles_fin >> cur;
			obstacles[i][j] = (cur=='1');
		}
	}

	std::ifstream objects_fin("data/rooms/"+roomName+"/objects.json");
	objects_fin >> objects;

}

// void Room::initialize(std::string roomName){
//     this->roomName = roomName;

//     // this should probably be room specific...
//     bg_texture.loadFromFile("data/imgs/tileMap.png");
//     bg_sprite.setTexture(bg_texture);
//     bg_sprite.setTextureRect(sf::IntRect(0, 0, WOLRD_DIMENSIONS.x, WOLRD_DIMENSIONS.y)); // seems sketchy....

//     rock_texture.loadFromFile("data/imgs/rock.png");
//     rock_sprite.setTexture(rock_texture);
//     rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));

//     teleporter_texture.loadFromFile("data/imgs/teleporter.png");
//     teleporter_sprite.setTexture(teleporter_texture);
//     teleporter_sprite.setScale(TILE_WIDTH/(1.0*teleporter_sprite.getTextureRect().width), TILE_WIDTH/(1.0*teleporter_sprite.getTextureRect().height));

//     dialogue_prompt_texture.loadFromFile("data/imgs/dialoguePrompt.png");
//     dialogue_prompt_sprite.setTexture(dialogue_prompt_texture);
//     dialogue_prompt_sprite.setScale(TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().width), TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().height));

//     std::ifstream obstacles_fin("data/rooms/"+roomName+"/obstacles.txt");
//     for(int i = 0; i < NUM_TILES; i++){
//         for(int j = 0; j < NUM_TILES; j++){
//             char cur;
//             obstacles_fin >> cur;
//             obstacles[i][j] = (cur=='1');
//         }
//     }

//     std::ifstream objects_fin("data/rooms/"+roomName+"/objects.json");
//     objects_fin >> objects;

// }

void Room::draw(sf::RenderWindow *window){
	window->draw(bg_sprite);

	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			if(obstacles[i][j]){
				const sf::Vector2f cur_pos(TILE_WIDTH*j, TILE_WIDTH*i);
				rock_sprite.setPosition(cur_pos);
				window->draw(rock_sprite);
			}
		}
	}

	for(json::iterator it = objects.begin(); it!=objects.end(); ++it){
		sf::Vector2f tmp((*it)["pos"][0], (*it)["pos"][1]);
		tmp = tmp*(1.0f*TILE_WIDTH);
		if((*it)["type"] == "dialogue"){
			dialogue_prompt_sprite.setPosition(tmp);
			window->draw(dialogue_prompt_sprite);
		}
		else if((*it)["type"] == "teleporter") {
			teleporter_sprite.setPosition(tmp);
			window->draw(teleporter_sprite);
		}
	}
}

bool Room::collidesWithObstacles(sf::Vector2i tile_pos){
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			if(obstacles[i][j]){
				if(tile_pos.x == j && tile_pos.y == i){
					return true;
				}
			}
		}
	}
	return false;
}

void Room::handleObjectCollisions(Player *player, Dialogue *dialogue){
	for(json::iterator it = objects.begin(); it!=objects.end(); ++it){
		sf::Vector2i tmp((*it)["pos"][0], (*it)["pos"][1]);
		if(player->getTilePos() == tmp){
			if((*it)["type"] == "dialogue"){
				dialogue->setOpenState(true);
				dialogue->updateText((*it)["body"]["description"], (*it)["body"]["title"]);
			}
			else if((*it)["type"] == "teleporter"){
				sf::Vector2i newPos;
				newPos.x = (*it)["body"]["newPos"][0];
				newPos.y = (*it)["body"]["newPos"][1];
				player->teleport((*it)["body"]["newRoom"], newPos);
			}
		}
	}
}

std::string Room::getName(){
	return roomName;
}
