
#include "Enemy.hpp"

Enemy::Enemy(){
	numAniFrames = new int[9] {6,6,4,4,3,4,4,4,4};
	visualDimensions.x = 80; visualDimensions.y = 80;
	texture.loadFromFile("data/imgs/mage_sheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,visualDimensions.x,visualDimensions.y));
	tile_pos.x = 3; tile_pos.y = 3;
	draw_pos.x = tile_pos.x*TILE_WIDTH; draw_pos.y = tile_pos.y*TILE_WIDTH; 
	health = 10;
}

void Enemy::wander(sf::Vector2i roomDimensions){
	int dx = 0; int dy = 0;
	int curRand = rand()%100;
	int moveSize = 1; // right now collisions depend on this being 1 (which is kinda sketch)
	if (curRand == 0){
		if (tile_pos.x < roomDimensions.x-moveSize)
			dx = moveSize;
	} 
	else if(curRand == 1){
		if(tile_pos.x > moveSize-1)
			dx = -moveSize;
	}
	else if(curRand == 2){
		if(tile_pos.y < roomDimensions.y-moveSize)
			dy = moveSize;
	}
	else if(curRand == 3){
		if(tile_pos.y > moveSize-1)
			dy = -moveSize;
	}
	
	setPos(tile_pos.x+dx, tile_pos.y+dy);
}

