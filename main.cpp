
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#include "Player.hpp"
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

	Room startRoom;
	startRoom.initialize();

	sf::Vector2f cameraPos;
	cameraPos.x = 0; cameraPos.y = 0;
	Player player;
	player.initialize();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				scaleViews(&window, &mainView, &dialogue);
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Q)
					window.close();
				else if(event.key.code == sf::Keyboard::C)
						dialogue.setOpenState(false);
				else{
					sf::Vector2f proposedPos(player.getPos().x, player.getPos().y);
					if(event.key.code == sf::Keyboard::A)
						proposedPos.x -= 10;
					else if(event.key.code == sf::Keyboard::D)
						proposedPos.x += 10;
					else if(event.key.code == sf::Keyboard::W)
						proposedPos.y -= 10;
					else if(event.key.code == sf::Keyboard::S)
						proposedPos.y += 10;
					if(!startRoom.collidesWithObstacles(proposedPos)){
						player.setPos(proposedPos.x, proposedPos.y);
					}
				}
			}
		}

		updateCameraPos(&cameraPos, player.getPos());
		mainView.setCenter(cameraPos);

        window.clear(BLACK);
		window.setView(mainView);

		startRoom.draw(&window);
		startRoom.handleObjectCollisions(player.getPos(), &dialogue);
		player.draw(&window);

		if(dialogue.isOpen()){
			dialogue.draw(&window);
		}

        window.display();
    }
    return 0;
}

