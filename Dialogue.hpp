#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "TextDisplay.hpp"
class Dialogue : public TextDisplay {
	private:
		bool dialogueOpen = false;
		sf::Vertex dialogueBackdrop[4];
		sf::Sprite faceSprite;
	public:
		Dialogue();
		void updateText(std::string newText, std::string newTitle);
		void draw(sf::RenderWindow *window);
		void setOpenState(bool isOpen);
		bool isOpen();
		void setSpriteTexture(sf::Texture *texture);
};
#endif // DIALOGUE_H
