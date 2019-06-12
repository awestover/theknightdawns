#ifndef PLAYER
#define PLAYER value
#include <SFML/Graphics.hpp>
class Player{
	private:
		sf::Texture dog_texture;
		sf::Sprite dog_sprite;
		sf::Vector2f draw_pos;
		sf::Vector2i tile_pos;
		float draw_catchup_speed = 4;
	public:
		void initialize();
		void draw(sf::RenderWindow *window);
		void setPos(int xpos, int ypos);
		sf::Vector2i getTilePos();
		sf::Vector2f getDrawPos();
		bool positionsSynced();
};
#endif /* ifndef PLAYER */
