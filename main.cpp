#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window;
	// window.create(sf::VideoMode(800, 800, 32), "RPG GAMMUUU!!", sf::Style::Fullscreen);
	window.create(sf::VideoMode(800, 800, 32), "RPG GAMMUUU!!");
	window.setFramerateLimit(60);

	sf::View mainView(sf::Vector2f(800/2, 800/2), sf::Vector2f(800, 800));
	mainView.setViewport(sf::FloatRect(0.0, 0.0, 1.0, 1.0));

	// Load background img
	sf::Texture texture;
	texture.loadFromFile("data/tileMap.png");
	sf::Sprite background;
	background.setTexture(texture);

	// sf::Vector2f cameraPos = new sf::Vector2f(0, 0);
	sf::Vector2f cameraPos();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					std::cout<<("hai")<<std::endl;
					break;
				case sf::Event::KeyPressed: 
					if (event.key.code == sf::Keyboard::Q)
						window.close();
					break;
				default:
					break;
					
			}
        }

        window.clear(sf::Color(0, 0, 0, 1));
		window.setView(mainView);

		background.setTextureRect(sf::IntRect(100, 100, 800, 800));
        window.draw(background);
        window.display();
    }

    return 0;
}

