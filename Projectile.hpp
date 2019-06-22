#ifndef PROJECTILE_H
#define PROJECTILE_H value
#include "Mover.hpp"
class Projectile : public Mover {
	private:
		bool active = false;
		int projectileRechargeFrames = 100;
		int projectileActiveFrameCt = 0;
		sf::Vector2i moveDirection;
	public: 
		Projectile();
		bool isActive();
		void activate(sf::Vector2i startPos, sf::Vector2i direction);
		void draw(sf::RenderWindow *window);
		void setProjectileRechargeFrames(int projectileRechargeFrames);
};
#endif /* ifndef PROJECTILE_H */
