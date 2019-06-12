
#include <iostream>
#include <math.h>

#include "Player.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

void Player::initialize() {
	tile_pos.x = 1; tile_pos.y = 1;
	draw_pos.x = tile_pos.x*TILE_WIDTH; draw_pos.y = tile_pos.y*TILE_WIDTH; 
	dog_texture.loadFromFile("data/imgs/turtle_sheet.png");
	dog_sprite.setTexture(dog_texture);
	dog_sprite.setTextureRect(sf::IntRect(0,0,TILE_WIDTH,TILE_WIDTH));
}

void Player::draw(sf::RenderWindow *window) {
	dog_sprite.setPosition(draw_pos);

	if(!positionsSynced()){
		int dx = TILE_WIDTH*tile_pos.x - draw_pos.x;
		int dy = TILE_WIDTH*tile_pos.y - draw_pos.y;
		if(fabs(dx) > draw_catchup_speed*0.5f){
			if(dx < 0){
				facing = LEFT;
				draw_pos.x -= draw_catchup_speed;
			}
			else { // dx > 0
				facing = RIGHT;
				draw_pos.x += draw_catchup_speed;
			}
		}
		else { // fabs(dy) > draw_catchup_speed*0.5f
			if(dy < 0){
				facing = UP;
				draw_pos.y -= draw_catchup_speed;
			}
			else { // dy > 0
				facing = DOWN;
				draw_pos.y += draw_catchup_speed;
			}
		}
	}

	aniCt += 1;
	if(aniCt == aniTurnOverCt){
		aniCt = 0;
		aniState = (aniState + 1) % numAniStates;
	}

	dog_sprite.setTextureRect(sf::IntRect(TILE_WIDTH*aniState, facing*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH));
	window->draw(dog_sprite);
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

