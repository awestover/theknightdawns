#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H value
#include "SFML/Graphics.hpp"
#include "constants.hpp"
#include <iostream>
class TextDisplay {
	protected:
		sf::View view;
		float TEXT_PADDING = 10.0f;
		int TEXT_SIZE = 20;
		sf::Font font;
		std::map<std::string, sf::Text*> texts;
		void initializeText(sf::Text *text, float x, float y, std::string initString);
	public:
		void setViewport(sf::FloatRect viewport);
};
#endif /* ifndef TEXT_DISPLAY_H */
