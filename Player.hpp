#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "constants.hpp"

class Player{
	private:
		sf::Vector2f visualDimensions;  // size of the image (on tilemaps collisions are still based on what tile the user is in, specifically what tile the user is standing in)
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f draw_pos;
		sf::Vector2i tile_pos;
		float draw_catchup_speed = 4; // basically speed. The character can update tile_pos by a discrete amount when positions are synced, and while positions are not synced this is the number of pixels per frame that we update towards being in sync
		const int numAniFrames[9] = {6,6,5,5,4,3,3,3,3}; // number of columns in each row of the sprite sheet
		int aniDirection = RIGHT;
		int aniFrame = 0;
		const int aniTurnOverCt = 10; // how many counts of aniCt to stay on a single frame 
		int aniCt = 0;
		std::string curRoom;
		std::string username;
		json userData;
		json quests;
		int getCurrentQuestIndex();
		void writeUserData();
	public:
	 	Player(std::string roomName, std::string username);
		void draw(sf::RenderWindow *window);
		void setPos(int xpos, int ypos);
		sf::Vector2i getTilePos();
		sf::Vector2f getDrawPos();
		bool positionsSynced();
		std::string getCurRoom();
		void teleport(std::string newRoom, sf::Vector2i newPos);
		bool questCompleted();
		void updateQuest();
		void updateQuestProgress(std::string id);
		int getHealth();
		std::string getCurrentQuest();
};
#endif /* ifndef PLAYER_H */
