
#include <iostream>
#include "Projectile.hpp"

Projectile::Projectile(){
	draw_catchup_speed = 6;
	numAniFrames = new int[9] {75,75,75,75,75,75,75,75,75};
	visualDimensions.x = 100; visualDimensions.y = 100;
	changePos(1,10);
	texture.loadFromFile("data/imgs/projectile_sheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,visualDimensions.x,visualDimensions.y));
}

bool Projectile::isActive() {
	return active;
}

void Projectile::activate(sf::Vector2i startPos, sf::Vector2i direction){
	changePos(startPos.x, startPos.y);
	active = true;
	moveDirection.x = direction.x;
	moveDirection.y = direction.y;
}

void Projectile::draw(sf::RenderWindow *window) {
	if(active){
		Mover::draw(window);
		projectileActiveFrameCt += 1;
		if (projectileActiveFrameCt > projectileRechargeFrames){
			projectileActiveFrameCt = 0;
			active = false;
		}
		if(positionsSynced()){
			setPos(tile_pos.x+moveDirection.x, tile_pos.y+moveDirection.y);
		}
	}
}

void Projectile::setProjectileRechargeFrames(int projectileRechargeFrames){
	this->projectileRechargeFrames = projectileRechargeFrames;
}

