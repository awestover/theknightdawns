#ifndef PLAYER
#define PLAYER value
#include <SFML/Graphics.hpp>

#include "constants.hpp"

class Player{
	private:
		sf::Texture dog_texture;
		sf::Sprite dog_sprite;
		sf::Vector2f draw_pos;
		sf::Vector2i tile_pos;
		float draw_catchup_speed = 4;
		const int numAniStates = 2;
		const int aniTurnOverCt = 10;
		int facing = RIGHT;
		int aniState = 0;
		int aniCt = 0;
	public:
		void initialize();
		void draw(sf::RenderWindow *window);
		void setPos(int xpos, int ypos);
		sf::Vector2i getTilePos();
		sf::Vector2f getDrawPos();
		bool positionsSynced();
};
#endif /* ifndef PLAYER */
