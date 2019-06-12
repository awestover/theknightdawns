
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#include "Player.hpp"
#include "Room.hpp"
#include "Dialogue.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

int main() {
	bool fullScreen = false;

	sf::RenderWindow window;
	if(fullScreen)
		window.create(sf::VideoMode(NUM_TILES*TILE_WIDTH, NUM_TILES*TILE_WIDTH, 32), "RPG GAMMUUU!!", sf::Style::Fullscreen);
	else
		window.create(sf::VideoMode(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, 32), "RPG GAMMUUU!!");
	window.setFramerateLimit(FRAME_RATE);

	sf::View mainView;
	mainView.setSize(SCREEN_DIMENSIONS);
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
			}
		}

		if(player.positionsSynced()){
			bool oneUpDownPressed = ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ^ (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));
			bool oneLeftRightPressed = ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ^ (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));
			if(oneUpDownPressed ^ oneLeftRightPressed){
				sf::Vector2i proposedPos(player.getTilePos().x, player.getTilePos().y);
				if(oneUpDownPressed){
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
						proposedPos.x -= 1;
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
						proposedPos.x += 1;
				}
				else { // oneUpDownPressed
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
						proposedPos.y -= 1;
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
						proposedPos.y += 1;
				}
				if(!startRoom.collidesWithObstacles(proposedPos)){
					player.setPos(proposedPos.x, proposedPos.y);
				}
			}
		}

		updateCameraPos(&cameraPos, player.getDrawPos());
		mainView.setCenter(cameraPos);

        window.clear(BLACK);
		window.setView(mainView);

		startRoom.draw(&window);
		startRoom.handleObjectCollisions(player.getTilePos(), &dialogue);
		player.draw(&window);

		if(dialogue.isOpen()){
			dialogue.draw(&window);
		}

        window.display();
    }

    return 0;
}

