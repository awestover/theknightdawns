#include <math.h>
#include <iostream>
#include "Entity.hpp"

void Entity::handleAttack(int damage){
	health -= damage;
	health = health < 0 ? 0 : health;
}

int Entity::getAttack(){
	return attack;
}

void Entity::draw(sf::RenderWindow *window){
	projectile.draw(window);
	Mover::draw(window);
	if (aniDirection < IDLE){
		attackDirection = aniDirection + 5;
	}
	else if(attackDirection > IDLE && !projectile.isActive()){
		aniDirection -= 5;
	}
}

void Entity::launchAttack(){
	sf::Vector2i projectileDirection(0, 0);
	if(attackDirection == 5)
		projectileDirection.x = 1;
	else if(attackDirection == 6)
		projectileDirection.x = -1;
	else if(attackDirection == 7)
		projectileDirection.y = -1;
	else if(attackDirection == 8)
		projectileDirection.y = 1;
	projectile.activate(tile_pos, projectileDirection);
	aniDirection = attackDirection;
}

bool Entity::attackReady() {
	return !projectile.isActive();
}

