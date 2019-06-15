#ifndef ROOM
#define ROOM
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>

#include "constants.hpp"
#include "Dialogue.hpp"
#include "Player.hpp"

class Room {
	private:
		bool obstacles[NUM_TILES][NUM_TILES];
		json objects;
		sf::Texture rock_texture, teleporter_texture, dialogue_prompt_texture, bg_texture;
		sf::Sprite rock_sprite, teleporter_sprite, dialogue_prompt_sprite, bg_sprite;
		std::string roomName;
	public:
		Room(std::string roomName);
		void draw(sf::RenderWindow *window);
		bool collidesWithObstacles(sf::Vector2i tile_pos);
		void handleObjectCollisions(Player *player, Dialogue *dialogue);
		std::string getName();
};
#endif // ROOM
