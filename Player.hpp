#ifndef PLAYER
#define PLAYER value
#include <SFML/Graphics.hpp>
class Player{
	private:
		sf::Texture dog_texture;
		sf::Sprite dog_sprite;
		sf::Vector2f pos;
	public:
		void initialize();
		void draw(sf::RenderWindow *window);
		void setPos(float xpos, float ypos);
		sf::Vector2f getPos();
};
#endif /* ifndef PLAYER */
