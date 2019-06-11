#ifndef DIALOGUE
#define DIALOGUE
class Dialogue{
	private:
		const float TEXT_PADDING = 10.0f;
		const int TEXT_SIZE = 20;
		sf::View dialogueView;
		sf::Font font;
		sf::Text dialogueText;
		sf::Text dialogueClose;
		sf::Vertex dialogueBackdrop[4];
	public:
		void initialize();
		void updateText(std::string newText);
		void draw(sf::RenderWindow *window);
		void setDialogueViewViewport(sf::FloatRect viewport);
};
#endif // DIALOGUE
