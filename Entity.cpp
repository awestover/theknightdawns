#include <math.h>
#include <iostream>
#include "Entity.hpp"

void Entity::handleAttack(int damage, BattleStats *battleStats, std::string name){
	health -= damage;
	health = health < 0 ? 0 : health;
	battleStats->updateHealth(name, health);
}

int Entity::getAttack(){
	return attack;
}

int Entity::getHealth(){
	return health;
}

void Entity::draw(sf::RenderWindow *window){
	projectile.draw(window);
	Mover::draw(window);
	if (aniDirection < IDLE){
		attackDirection = aniDirection + 5;
	}
	else if(attackDirection > IDLE && !projectile.isMoving()){
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
	projectile.fire(tile_pos, projectileDirection);
	aniDirection = attackDirection;
}

bool Entity::attackReady() {
	return projectile.isCharged();
}

bool Entity::shootingProjectile(){
	return projectile.isMoving();
}

void Entity::handleProjectileCollisions(Entity *other, BattleStats *battleStats, std::string victim){
	if(projectile.isMoving()){
		// weird thing: what if positions aren't synced!!! 
		// temporary solution: don't care about it
		if (other->getTilePos().x == projectile.getTilePos().x && other->getTilePos().y == projectile.getTilePos().y){
			other->handleAttack(getAttack(), battleStats, victim);
			projectile.handleHit();
		}
	}
}

bool Entity::isDead(){
	return health <= 0;
}
