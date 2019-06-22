#ifndef ENTITY_H
#define ENTITY_H value
#include "Mover.hpp"
#include "Projectile.hpp"
#include "BattleStats.hpp"

class Entity : public Mover {
	protected:
		int health = 0;
		int attack = 1;
		Projectile projectile;
		int attackDirection = 5; // 5678 are the attack directions
	public:
		void handleAttack(int damage, BattleStats *battleStats, std::string name);
		int getAttack();
		void draw(sf::RenderWindow *window);
		bool attackReady();
		bool shootingProjectile();
		void launchAttack();
		void handleProjectileCollisions(Entity *other, BattleStats *battleStats, std::string victim);
		int getHealth();
		bool isDead();
};
#endif /* ifndef ENTITY_H */
