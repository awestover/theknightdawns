#ifndef DIALOGUE_H
#define DIALOGUE_H
#include <SFML/Graphics.hpp>
class Dialogue{
	private:
		const float TEXT_PADDING = 10.0f;
		const int TEXT_SIZE = 20;
		bool dialogueOpen = false;
		sf::View dialogueView;
		sf::Font font;
		sf::Text dialogueText, dialogueTitle, dialogueClose;
		sf::Vertex dialogueBackdrop[4];
		void initializeText(sf::Text *text, float x, float y, std::string initString);
		sf::Sprite faceSprite;
	public:
		Dialogue();
		void updateText(std::string newText, std::string newTitle);
		void draw(sf::RenderWindow *window);
		void setDialogueViewViewport(sf::FloatRect viewport);
		void setOpenState(bool isOpen);
		bool isOpen();
		void setSpriteTexture(sf::Texture *texture);
};
#endif // DIALOGUE_H
