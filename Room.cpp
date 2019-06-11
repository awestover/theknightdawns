
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

#include "utilityFunctions.hpp"
#include "Room.hpp"

void Room::initialize(){
	rock_texture.loadFromFile("data/imgs/rock.png");
	rock_sprite.setTexture(rock_texture);
	rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));

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
	std::cout<<objects["objectNames"]<<std::endl;

}

void Room::draw(sf::RenderWindow *window){
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			if(obstacles[i][j]){
				const sf::Vector2f cur_pos(TILE_WIDTH*j, TILE_WIDTH*i);
				rock_sprite.setPosition(cur_pos);
				window->draw(rock_sprite);
			}
		}
	}

	sf::Vector2f tmp(objects["quest1"]["pos"][0], objects["quest1"]["pos"][1]);
	tmp = tmp*(1.0f*TILE_WIDTH);
	rock_sprite.setPosition(tmp);
	window->draw(rock_sprite);
}

void Room::handleCollisions(sf::Sprite *dog_sprite, Dialogue *dialogue){
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			if(obstacles[i][j]){
				const sf::Vector2f cur_pos(TILE_WIDTH*j, TILE_WIDTH*i);
				if(tileHitsTile(cur_pos, dog_sprite->getPosition())){
					dialogue->setOpenState(true);
					std::stringstream ss;
					ss<<"collision with: "<<i<<","<<j;
					dialogue->updateText(ss.str());
				}
			}
		}
	}

	sf::Vector2f tmp(objects["quest1"]["pos"][0], objects["quest1"]["pos"][1]);
	tmp = tmp*(1.0f*TILE_WIDTH);
	if(tileHitsTile(tmp, dog_sprite->getPosition())){
		dialogue->setOpenState(true);
		if(objects["quest1"]["type"] == "dialogue"){
			dialogue->updateText(objects["quest1"]["body"]);
		}
	}
}

