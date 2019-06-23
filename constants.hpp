#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "SFML/Graphics.hpp"
const int TILE_WIDTH = 64;
const sf::Vector2f SCREEN_DIMENSIONS(TILE_WIDTH*16, TILE_WIDTH*12);
const sf::Vector2f DIALOGUE_DIMENSIONS(SCREEN_DIMENSIONS.x, 150);
const sf::Vector2f BATTLE_STATS_DIMENSIONS(SCREEN_DIMENSIONS.x, 100);
const sf::Vector2f HUD_DIMENSIONS(SCREEN_DIMENSIONS.x, 40);
const float DIALOGUE_VIEWPORT_RELATIVE_HEIGHT = 0.3;
const float BATTLE_STATS_VIEWPORT_RELATIVE_HEIGHT = 0.2;
const float HUD_VIEWPORT_RELATIVE_HEIGHT = 0.04;
const sf::Color BLACK(0,0,0);
const int FRAME_RATE = 80;
/*! \enum DIRECTIONS
 * in my sprite sheets we are going to follow the conventions that
 * 	- sprites are TILE_WIDTH X TILE_WIDTH
 * 	- each row of sprites has the animations for a sprite in a given direction
 * 	- each row represents a different direction
 * 	- DO NOT CHANGE THIS ENUM, everything will break!!!!
 */
enum DIRECTIONS { RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3, IDLE = 4, ATTACK_RIGHT = 5, ATTACK_LEFT = 6, ATTACK_UP = 7, ATTACK_DOWN = 8 };
#endif // CONSTANTS_H
