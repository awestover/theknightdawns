
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "utilityFunctions.hpp"
#include "Room.hpp"

void Room::initialize(){
	bg_texture.loadFromFile("data/imgs/tileMap.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setTextureRect(sf::IntRect(0, 0, WOLRD_DIMENSIONS.x, WOLRD_DIMENSIONS.y)); // seems sketchy....

	rock_texture.loadFromFile("data/imgs/rock.png");
	rock_sprite.setTexture(rock_texture);
	rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));

	dialogue_prompt_texture.loadFromFile("data/imgs/dialoguePrompt.png");
	dialogue_prompt_sprite.setTexture(dialogue_prompt_texture);
	dialogue_prompt_sprite.setScale(TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().width), TILE_WIDTH/(1.0*dialogue_prompt_sprite.getTextureRect().height));

	std::ifstream obstacles_fin("data/rooms/startRoom/obstacles.txt");
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			char cur;
			obstacles_fin >> cur;
			obstacles[i][j] = (cur=='1');
		}
	}

	std::ifstream objects_fin("data/rooms/startRoom/objects.json");
	objects_fin >> objects;

}

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
		dialogue_prompt_sprite.setPosition(tmp);
		window->draw(dialogue_prompt_sprite);
	}
}

// Given: position of the top left corner of a rectangle with dimensions TILE_WIDTH by TILE_WIDTH
// Returns true if the position overlaps with any obstacle tiles
bool Room::collidesWithObstacles(sf::Vector2i pos){
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			if(obstacles[i][j]){
				if(pos.x == j && pos.y == i){
					return true;
				}
			}
		}
	}
	return false;
}

void Room::handleObjectCollisions(sf::Vector2i pos, Dialogue *dialogue){
	for(json::iterator it = objects.begin(); it!=objects.end(); ++it){
		sf::Vector2i tmp((*it)["pos"][0], (*it)["pos"][1]);
		if(pos == tmp){
			dialogue->setOpenState(true);
			if((*it)["type"] == "dialogue"){
				dialogue->updateText((*it)["body"]["description"], (*it)["body"]["title"]);
			}
		}
	}
}

