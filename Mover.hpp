#ifndef MOVER_H
#define MOVER_H value
#include "Animated.hpp"
class Mover : public Animated {
	protected:
		sf::Vector2i tile_pos;
		float draw_catchup_speed = 4; // basically speed. The character can update tile_pos by a discrete amount when positions are synced, and while positions are not synced this is the number of pixels per frame that we update towards being in sync
	public:
		sf::Vector2i getTilePos();
		bool positionsSynced();
		void draw(sf::RenderWindow *window);
		void setPos(int xpos, int ypos);
		void changePos(int xpos, int ypos);
};
#endif /* ifndef MOVER_H */
