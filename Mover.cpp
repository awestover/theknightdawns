#include <math.h>
#include "Mover.hpp"

void Mover::setPos(int xpos, int ypos){
	tile_pos.x = xpos;
	tile_pos.y = ypos;
}

void Mover::changePos(int xpos, int ypos){
	tile_pos.x = xpos;
	tile_pos.y = ypos;
	draw_pos.x = TILE_WIDTH*xpos;
	draw_pos.y = TILE_WIDTH*ypos;
}

void Mover::draw(sf::RenderWindow *window) {
	sprite.setPosition(draw_pos.x - (visualDimensions.x - TILE_WIDTH), draw_pos.y - (visualDimensions.y - TILE_WIDTH));

	if(!positionsSynced()){
		int dx = TILE_WIDTH*tile_pos.x - draw_pos.x;
		int dy = TILE_WIDTH*tile_pos.y - draw_pos.y;
		if(fabs(dx) > draw_catchup_speed*0.5f){
			if(dx < 0){
				if(aniDirection <= IDLE)
					aniDirection = LEFT;
				draw_pos.x -= draw_catchup_speed;
			}
			else { // dx > 0
				if(aniDirection <= IDLE)
					aniDirection = RIGHT;
				draw_pos.x += draw_catchup_speed;
			}
		}
		else { // fabs(dy) > draw_catchup_speed*0.5f
			if(dy < 0){
				if(aniDirection <= IDLE)
					aniDirection = UP;
				draw_pos.y -= draw_catchup_speed;
			}
			else { // dy > 0
				if(aniDirection <= IDLE)
					aniDirection = DOWN;
				draw_pos.y += draw_catchup_speed;
			}
		}
	}
	else {
		if(aniDirection <= IDLE)
			aniDirection = IDLE;
	}

	aniCt += 1;
	if(aniCt == aniTurnOverCt){
		aniCt = 0;
		aniFrame = (aniFrame + 1) % numAniFrames[aniDirection];
	}

	sprite.setTextureRect(sf::IntRect(aniFrame*visualDimensions.x, aniDirection*visualDimensions.y, visualDimensions.x, visualDimensions.y));
	window->draw(sprite);
}

bool Mover::positionsSynced(){
	bool xSynced = fabs(draw_pos.x - TILE_WIDTH*tile_pos.x) < draw_catchup_speed*0.5f;
	bool ySynced = fabs(draw_pos.y - TILE_WIDTH*tile_pos.y) < draw_catchup_speed*0.5f;
	return xSynced & ySynced;
}

// getters
sf::Vector2i Mover::getTilePos(){
	return tile_pos;
}

sf::Vector2f Mover::getDrawPos(){
	return draw_pos;
}
