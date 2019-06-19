
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <string>
#include <fstream>
#include <map>

#include "Player.hpp"
#include "Room.hpp"
#include "Dialogue.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"
#include "HUD.hpp"

void shutdown(int numRooms, sf::RenderWindow *window, Room **rooms){
	window->close();
	for (int i = 0; i < numRooms; ++i) {
		free(rooms[i]);
	}
	free(rooms);
}

int main(int argc, char** argv) {
	std::string username;
	if (argc == 2){
		username = argv[1];
	}
	else {
		username = "null";
	}
	bool battleMode = false; // 2 modes, battle mode and normal mode
	bool fullScreen = false;
	sf::RenderWindow window;
	if(fullScreen)
		window.create(sf::VideoMode(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, 32), "RPG GAMMUUU!!", sf::Style::Fullscreen);
	else
		window.create(sf::VideoMode(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, 32), "RPG GAMMUUU!!");
	window.setFramerateLimit(FRAME_RATE);

	sf::View mainView;
	mainView.setSize(SCREEN_DIMENSIONS);

	std::ifstream roomFin("data/rooms/rooms.txt");
	int numRooms;
	roomFin>>numRooms;
	std::map<std::string, int> roomNameIdxs;
	for (int i = 0; i < numRooms; ++i) {
		std::string tmp;
		roomFin>>tmp;
		roomNameIdxs.insert(std::pair<std::string, int>(tmp, i));
	}
	Room **rooms = (Room**)malloc(sizeof(Room)*numRooms);
	for(std::map<std::string, int>::iterator itr = roomNameIdxs.begin(); itr != roomNameIdxs.end(); ++itr)
		rooms[itr->second] = new Room(itr->first);

	Player player(rooms[0]->getName(), username);
	Dialogue dialogue;
	HUD hud(username, player.getCurrentQuest()); // tbh hud should be a private field of player....
	scaleViews(&window, &mainView, &dialogue, &hud);
	hud.setRoom(player.getCurRoom());
	if(player.questCompleted())
		player.updateQuest();

	sf::Vector2f cameraPos;
	cameraPos.x = 0; cameraPos.y = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				shutdown(numRooms, &window, rooms);
			}
			else if (event.type == sf::Event::Resized) {
				scaleViews(&window, &mainView, &dialogue, &hud);
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Q)
					shutdown(numRooms, &window, rooms);
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
				if(!rooms[roomNameIdxs[player.getCurRoom()]]-> collidesWithObstacles(proposedPos)){
					player.setPos(proposedPos.x, proposedPos.y);
				}
			}
		}

		updateCameraPos(&cameraPos, player.getDrawPos(), rooms[roomNameIdxs[player.getCurRoom()]]->getDimensions());
		mainView.setCenter(cameraPos);
        window.clear(BLACK);
		window.setView(mainView);

		rooms[roomNameIdxs[player.getCurRoom()]]->draw(&window);
		rooms[roomNameIdxs[player.getCurRoom()]]->handleObjectCollisions(&player, &dialogue, &hud);
		player.draw(&window);
		hud.draw(&window);

		if(dialogue.isOpen()){
			dialogue.draw(&window);
		}

        window.display();
    }

    return 0;
}

