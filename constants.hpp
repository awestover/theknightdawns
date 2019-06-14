#ifndef CONSTANTS
#define CONSTANTS
#include <SFML/Graphics.hpp>
// NOTE: tilemap is 32*64 X 32*64
const int NUM_TILES = 32;
const int TILE_WIDTH = 64;
const sf::Vector2f SCREEN_DIMENSIONS(1024, 256*3);
const sf::Vector2f WOLRD_DIMENSIONS(NUM_TILES*TILE_WIDTH, NUM_TILES*TILE_WIDTH);
const sf::Vector2f DIALOGUE_DIMENSIONS(SCREEN_DIMENSIONS.x, 100);
const float DIALOGUE_VIEWPORT_RELATIVE_HEIGHT = 0.2;
const sf::Color BLACK(0,0,0);
const int FRAME_RATE = 60;
/*! \enum DIRECTIONS
 * in my sprite sheets we are gonna follow the conventions that
 * 	- sprites are TILE_WIDTH X TILE_WIDTH
 * 	- each row of sprites has the animations for a sprite in a given dirrection
 * 	- each row represents a different direction
 * 	- 1st row is right
 * 	- 2nd row is left
 * 	- 3rd row is up
 * 	- 4th row is down
 */
enum DIRECTIONS { RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3, IDLE = 4, ATTACK_RIGHT = 5, ATTACK_LEFT = 6, ATTACK_UP = 7, ATTACK_DOWN = 8 };
#endif // CONSTANTS
