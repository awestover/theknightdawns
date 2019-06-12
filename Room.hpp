#ifndef ROOM
#define ROOM
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "constants.hpp"
#include "Dialogue.hpp"
class Room {
	private:
		bool obstacles[NUM_TILES][NUM_TILES];
		json objects;
		sf::Texture rock_texture, dialogue_prompt_texture, bg_texture;
		sf::Sprite rock_sprite, dialogue_prompt_sprite, bg_sprite;
	public:
		void initialize();
		void draw(sf::RenderWindow *window);
		bool collidesWithObstacles(sf::Vector2i pos);
		void handleObjectCollisions(sf::Vector2i pos, Dialogue *dialogue);
};
#endif // ROOM
