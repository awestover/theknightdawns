#ifndef ENTITY_H
#define ENTITY_H value
#include <SFML/Graphics.hpp>

#include "constants.hpp"

class Entity{
	protected:
		int *numAniFrames; // number of columns in each row of the sprite sheet
		sf::Vector2f visualDimensions;  // size of the image (on tilemaps collisions are still based on what tile the user is in, specifically what tile the user is standing in)
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f draw_pos;
		sf::Vector2i tile_pos;
		float draw_catchup_speed = 4; // basically speed. The character can update tile_pos by a discrete amount when positions are synced, and while positions are not synced this is the number of pixels per frame that we update towards being in sync
		int aniDirection = RIGHT;
		int aniFrame = 0;
		const int aniTurnOverCt = 10; // how many counts of aniCt to stay on a single frame 
		int aniCt = 0;
	public:
		sf::Vector2i getTilePos();
		sf::Vector2f getDrawPos();
		bool positionsSynced();
		void draw(sf::RenderWindow *window);
		void setPos(int xpos, int ypos);

};
#endif /* ifndef ENTITY_H */
