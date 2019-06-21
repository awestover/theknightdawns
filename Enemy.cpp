
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

void Enemy::wander(sf::Vector2i roomDimensions){
	int dx = 0; int dy = 0;
	int curRand = rand()%100;
	int moveSize = 5;
	if (curRand == 0){
		if (tile_pos.x < roomDimensions.x-moveSize)
			dx = 5;
	} 
	else if(curRand == 1){
		if(tile_pos.x > moveSize-1)
			dx = -5;
	}
	else if(curRand == 2){
		if(tile_pos.y < roomDimensions.y-moveSize)
			dy = 1;
	}
	else if(curRand == 3){
		if(tile_pos.y > moveSize-1)
			dy = -1;
	}
	
	setPos(tile_pos.x+dx, tile_pos.y+dy);
}

