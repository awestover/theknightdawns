#ifndef ANIMATED_H
#define ANIMATED_H value
#include "SFML/Graphics.hpp"
#include "constants.hpp"
#include <iostream>
class Animated {
	protected:
		int *numAniFrames; // number of columns in each row of the sprite sheet
		sf::Vector2f visualDimensions;  // size of the image (on tilemaps collisions are still based on what tile the user is in, specifically what tile the user is standing in)
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f draw_pos;
		int aniDirection = 0;
		int aniFrame = 0;
		int aniTurnOverCt = 10; // how many counts of aniCt to stay on a single frame 
		int aniCt = 0;
	public:
		Animated();
		Animated(sf::Vector2i dimensions, std::string spritePath);
		sf::Vector2f getDrawPos();
		void draw(sf::RenderWindow *window);
		void changePos(int xpos, int ypos);
};
#endif /* ifndef ANIMATED_H */
