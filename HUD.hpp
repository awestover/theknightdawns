#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
class HUD{
	private:
		const float TEXT_PADDING = 10.0f;
		const int TEXT_SIZE = 20;
		sf::View hudView;
		sf::Font font;
		sf::Text usernameText, roomText, questText;
		sf::Vertex bg[4];
	public:
		HUD(std::string username, std::string quest);
		void setRoom(std::string room);
		void draw(sf::RenderWindow *window);
		void setViewport(sf::FloatRect viewport);
		void setQuest(std::string title);
		void initializeText(sf::Text *text, float x, float y, std::string initString);
};
#endif /* ifndef HUD_H */
