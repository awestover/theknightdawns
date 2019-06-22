#ifndef ENTITY_H
#define ENTITY_H value
#include "Mover.hpp"
#include "Projectile.hpp"

class Entity : public Mover {
	protected:
		int health = 0;
		int attack = 1;
		Projectile projectile;
		int attackDirection = 5; // 5678 are the attack directions
	public:
		void handleAttack(int damage);
		int getAttack();
		void draw(sf::RenderWindow *window);
		bool attackReady();
		void launchAttack();
};
#endif /* ifndef ENTITY_H */
