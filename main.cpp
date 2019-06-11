
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#include "Room.hpp"
#include "Dialogue.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

int main()
{
	bool fullScreen = false;

	sf::RenderWindow window;
	if(fullScreen)
		window.create(sf::VideoMode(NUM_TILES*TILE_WIDTH, NUM_TILES*TILE_WIDTH, 32), "RPG GAMMUUU!!", sf::Style::Fullscreen);
	else
		window.create(sf::VideoMode(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, 32), "RPG GAMMUUU!!");
	window.setFramerateLimit(FRAME_RATE);

	sf::View mainView;
	mainView.setSize(sf::Vector2f(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y));

	Dialogue dialogue;
	dialogue.initialize();

	scaleViews(&window, &mainView, &dialogue);

	// Load images
	sf::Texture bg_texture;
	bg_texture.loadFromFile("data/imgs/tileMap.png");
	sf::Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);

	sf::Texture dog_texture;
	dog_texture.loadFromFile("data/imgs/dog.png");
	sf::Sprite dog_sprite;
	dog_sprite.setTexture(dog_texture);

	Room startRoom;
	startRoom.initialize();

	sf::Vector2f cameraPos; 
	cameraPos.x = 0; cameraPos.y = 0;
	sf::Vector2f userPos(TILE_WIDTH, TILE_WIDTH);

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
				scaleViews(&window, &mainView, &dialogue);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Q)
					window.close();
				else{
					sf::Vector2f proposedPos(userPos.x, userPos.y);
					if(event.key.code == sf::Keyboard::A)
						userPos.x -= 10;
					else if(event.key.code == sf::Keyboard::D)
						userPos.x += 10;
					else if(event.key.code == sf::Keyboard::W)
						userPos.y -= 10;
					else if(event.key.code == sf::Keyboard::S)
						userPos.y += 10;
					else if(event.key.code == sf::Keyboard::C)
						dialogue.setOpenState(false);
				}
			}
		}

		updateCameraPos(&cameraPos, userPos);
		mainView.setCenter(cameraPos);

        window.clear(BLACK);
		window.setView(mainView);

		bg_sprite.setTextureRect(sf::IntRect(0, 0, WOLRD_DIMENSIONS.x, WOLRD_DIMENSIONS.y));
		window.draw(bg_sprite);

		startRoom.draw(&window);
		startRoom.handleCollisions(&dog_sprite, &dialogue);

		dog_sprite.setPosition(userPos);
		window.draw(dog_sprite);

		if(dialogue.isOpen()){
			dialogue.draw(&window);
		}

        window.display();
    }
    return 0;
}

