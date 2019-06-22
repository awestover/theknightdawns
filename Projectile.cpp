
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

bool Projectile::isMoving() {
	return moving;
}

bool Projectile::isCharged() {
	return charged;
}

void Projectile::fire(sf::Vector2i startPos, sf::Vector2i direction){
	changePos(startPos.x, startPos.y);
	moving = true;
	charged = false;
	moveDirection.x = direction.x;
	moveDirection.y = direction.y;
}

void Projectile::handleHit(){
	moving = false;
}

void Projectile::draw(sf::RenderWindow *window) {
	if(moving){
		Mover::draw(window);
		if(positionsSynced()){
			setPos(tile_pos.x+moveDirection.x, tile_pos.y+moveDirection.y);
		}
	}
	if(!charged){
		projectileFrameCt += 1;
		if (projectileFrameCt > projectileRechargeFrames){
			projectileFrameCt = 0;
			moving = false;
			charged = true;
		}
	}
}

void Projectile::setProjectileRechargeFrames(int projectileRechargeFrames){
	this->projectileRechargeFrames = projectileRechargeFrames;
}

