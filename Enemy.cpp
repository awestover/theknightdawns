
#include "Enemy.hpp"

Enemy::Enemy(){
	numAniFrames = new int[9] {6,6,4,4,3,4,4,4,4};
	visualDimensions.x = 80; visualDimensions.y = 80;
	texture.loadFromFile("data/imgs/mage_sheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,visualDimensions.x,visualDimensions.y));
	tile_pos.x = 3; tile_pos.y = 3;
	draw_pos.x = tile_pos.x*TILE_WIDTH; draw_pos.y = tile_pos.y*TILE_WIDTH; 
}
