#ifndef ENEMY_H
#define ENEMY_H value
#include "Entity.hpp"
class Enemy : public Entity {
	private:
	public:
		Enemy();
		void wander(sf::Vector2i roomDimensions);
};
#endif /* ifndef ENEMY_H */
