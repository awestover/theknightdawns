
#include <iostream>
#include <math.h>

#include "Player.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

void Player::initialize() {
	tile_pos.x = 1; tile_pos.y = 1;
	draw_pos.x = tile_pos.x*TILE_WIDTH; draw_pos.y = tile_pos.y*TILE_WIDTH; 
	dog_texture.loadFromFile("data/imgs/dog.png");
	dog_sprite.setTexture(dog_texture);
}

void Player::draw(sf::RenderWindow *window) {
	dog_sprite.setPosition(draw_pos);
	window->draw(dog_sprite);

	if(!positionsSynced()){
		int dx = TILE_WIDTH*tile_pos.x - draw_pos.x;
		int dy = TILE_WIDTH*tile_pos.y - draw_pos.y;

		draw_pos.x += sgn(dx)*draw_catchup_speed;
		draw_pos.y += sgn(dy)*draw_catchup_speed;
	}
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

