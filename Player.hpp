#ifndef PLAYER_H
#define PLAYER_H
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "constants.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Dijkstra.hpp"

class Player : public Entity {
	private:
		std::string curRoom;
		std::string username;
		json userData;
		json quests;
		int getCurrentQuestIndex();
		void writeUserData();

		sf::Texture arrowTexture; 
		sf::Sprite arrowSprite;
		int arrowDims = 64;
		Dijkstra dijkstra;
	public:
	 	Player(std::string roomName, std::string username);
		std::string getCurRoom();
		void teleport(std::string newRoom, sf::Vector2i newPos);
		bool questCompleted();
		void updateQuest();
		void updateQuestProgress(std::string id);
		std::string getCurrentQuest();
		void drawArrow(sf::RenderWindow *window);
};
#endif /* ifndef PLAYER_H */
