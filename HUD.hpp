#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
#include "TextDisplay.hpp"
class HUD : public TextDisplay {
	private:
		sf::Vertex bg[4];
	public:
		HUD(std::string username, std::string quest);
		void setRoom(std::string room);
		void draw(sf::RenderWindow *window);
		void setQuest(std::string title);
};
#endif /* ifndef HUD_H */
