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
#endif // CONSTANTS
