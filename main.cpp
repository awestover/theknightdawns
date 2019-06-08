
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
	const int NUM_TILES = 25;
	const int TILE_WIDTH = 32;
	const sf::Vector2f screenDimensions(NUM_TILES*TILE_WIDTH, NUM_TILES*TILE_WIDTH);
	const sf::Vector2f worldDimensions(NUM_TILES*TILE_WIDTH, NUM_TILES*TILE_WIDTH);

	sf::RenderWindow window;
	// window.create(sf::VideoMode(800, 800, 32), "RPG GAMMUUU!!", sf::Style::Fullscreen);
	// mainView.setViewport(sf::FloatRect()); // should scale
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "RPG GAMMUUU!!");
	window.setFramerateLimit(60);

	sf::View mainView(sf::Vector2f(screenDimensions.x/2, screenDimensions.y/2), sf::Vector2f(screenDimensions.x, screenDimensions.y));
	mainView.setViewport(sf::FloatRect(0.0, 0.0, 1.0, 1.0));

	// Load images
	sf::Texture bg_texture;
	bg_texture.loadFromFile("data/tileMap.png");
	sf::Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);

	sf::Texture dog_texture;
	dog_texture.loadFromFile("data/dog.png");
	sf::Sprite dog_sprite;
	dog_sprite.setTexture(dog_texture);

	sf::Vector2f cameraPos(0, 0);
	sf::Vector2f userPos(0, 0);

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
				float rectWidth = screenDimensions.x/event.size.width;
				float rectHeight = screenDimensions.y/event.size.height;
				mainView.setViewport(sf::FloatRect((1-rectWidth)/2,(1-rectHeight)/2,rectWidth,rectHeight));
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Q)
					window.close();
				else if(event.key.code == sf::Keyboard::A)
					userPos.x -= 10;
				else if(event.key.code == sf::Keyboard::D)
					userPos.x += 10;
				else if(event.key.code == sf::Keyboard::W)
					userPos.y -= 10;
				else if(event.key.code == sf::Keyboard::S)
					userPos.y += 10;
			}
		}

		cameraPos.x = userPos.x + TILE_WIDTH/2;
		if (cameraPos.x < screenDimensions.x/2)
			cameraPos.x = screenDimensions.x/2;
		if (cameraPos.x > worldDimensions.x - screenDimensions.x/2)
			cameraPos.x = worldDimensions.x - screenDimensions.x/2;
		cameraPos.y = userPos.y + TILE_WIDTH/2;
		if (cameraPos.y < screenDimensions.y/2)
			cameraPos.y = screenDimensions.y/2;
		if (cameraPos.y > worldDimensions.y - screenDimensions.y/2)
			cameraPos.y = worldDimensions.y - screenDimensions.y/2;
		mainView.setCenter(cameraPos);

        window.clear(sf::Color(0, 0, 0, 1));
		window.setView(mainView);

		bg_sprite.setTextureRect(sf::IntRect(0, 0, screenDimensions.x, screenDimensions.y));
        window.draw(bg_sprite);
		dog_sprite.setPosition(userPos);
		window.draw(dog_sprite);

        window.display();
    }

    return 0;
}

