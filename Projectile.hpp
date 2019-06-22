#ifndef PROJECTILE_H
#define PROJECTILE_H value
#include "Mover.hpp"
class Projectile : public Mover {
	private:
		bool moving = false;
		bool charged = true;
		int projectileRechargeFrames = 100;
		int projectileFrameCt = 0;
		sf::Vector2i moveDirection;
	public: 
		Projectile();
		bool isMoving();
		bool isCharged();
		void fire(sf::Vector2i startPos, sf::Vector2i direction);
		void draw(sf::RenderWindow *window);
		void setProjectileRechargeFrames(int projectileRechargeFrames);
		void handleHit();
};
#endif /* ifndef PROJECTILE_H */
