#include <SFML/Graphics.hpp>
#include <iostream>
// #include <stdio.h>
using namespace std;

int main()
{
	const sf::Vector2f viewSize(800, 800);

	sf::RenderWindow window;
	// window.create(sf::VideoMode(800, 800, 32), "RPG GAMMUUU!!", sf::Style::Fullscreen);
	window.create(sf::VideoMode(viewSize.x, viewSize.y, 32), "RPG GAMMUUU!!");
	window.setFramerateLimit(60);

	sf::View mainView(sf::Vector2f(viewSize.x/2, viewSize.y/2), sf::Vector2f(viewSize.x, viewSize.y));
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
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				float rectWidth = viewSize.x/event.size.width;
				float rectHeight = viewSize.y/event.size.height;
				mainView.setViewport(sf::FloatRect((1-rectWidth)/2,(1-rectHeight)/2,rectWidth,rectHeight));
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Q)
					window.close();
			}
		}

        window.clear(sf::Color(0, 0, 0, 1));
		window.setView(mainView);

		background.setTextureRect(sf::IntRect(100, 100, viewSize.x, viewSize.y));
        window.draw(background);
        window.display();
    }

    return 0;
}

