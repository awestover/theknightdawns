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
		sf::Texture rock_texture;
		sf::Sprite rock_sprite;
	public:
		void initialize();
		void draw(sf::RenderWindow *window);
		void handleCollisions(sf::Sprite *dog_sprite, Dialogue *dialogue);
};
#endif // ROOM
