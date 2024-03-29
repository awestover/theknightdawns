#ifndef ROOM_H
#define ROOM_H
#include "SFML/Graphics.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <string>
#include <map>

#include "constants.hpp"
#include "Dialogue.hpp"
#include "HUD.hpp"
#include "Player.hpp"
#include "Animated.hpp"

class Room {
	private:
		std::string roomName;
		sf::Vector2i dimensions;
		bool **obstacles;
		json objects;
		std::map<std::string, Animated*> animatedObjects;
		sf::Texture rock_texture, dialogue_prompt_texture, bg_texture;
		sf::Sprite rock_sprite, dialogue_prompt_sprite, bg_sprite;
		sf::Vector2i teleporterDimensions;
		const int teleporterNumAniFrames = 61;
		int teleporterAniFrame = 0;
		const int teleporterAniTurnOverCt = 10; // how many counts of aniCt to stay on a single frame 
		int teleporterAniCt = 0;
	public:
		Room(std::string roomName);
		void draw(sf::RenderWindow *window, std::map<std::string, sf::Texture> *faces, bool battleMode);
		bool collidesWithObstacles(sf::Vector2i tile_pos);
		void handleObjectCollisions(Player *player, Dialogue *dialogue, HUD *hud, std::map<std::string, sf::Texture> *faces, bool *battleMode);
		std::string getName();
		sf::Vector2i getDimensions();
};
#endif // ROOM_H
