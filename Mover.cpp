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
	Animated::draw(window);
}

bool Mover::positionsSynced(){
	bool xSynced = fabs(draw_pos.x - TILE_WIDTH*tile_pos.x) < draw_catchup_speed*0.5f;
	bool ySynced = fabs(draw_pos.y - TILE_WIDTH*tile_pos.y) < draw_catchup_speed*0.5f;
	return xSynced & ySynced;
}

sf::Vector2i Mover::getTilePos(){
	return tile_pos;
}

