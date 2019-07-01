/***
 *        ___    __     __      _       __          __                      
 *       /   |  / /__  / /__   | |     / /__  _____/ /_____ _   _____  _____
 *      / /| | / / _ \/ //_/   | | /| / / _ \/ ___/ __/ __ \ | / / _ \/ ___/
 *     / ___ |/ /  __/ ,<      | |/ |/ /  __(__  ) /_/ /_/ / |/ /  __/ /    
 *    /_/  |_/_/\___/_/|_|     |__/|__/\___/____/\__/\____/|___/\___/_/     
 *                                                                          
 */
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <string>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <assert.h>

#include "Player.hpp"
#include "Room.hpp"
#include "Dialogue.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"
#include "HUD.hpp"
#include "BattleStats.hpp"
#include "Enemy.hpp"

int main(int argc, char** argv) {
	srand(time(NULL));
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

	std::ifstream facesFin("data/faces.txt");
	int numFaces;
	facesFin>>numFaces;
	std::map<std::string, sf::Texture> faces;
	for (int i = 0; i < numFaces; i++) {
		std::string faceName;
		facesFin>>faceName;
		sf::Texture faceSprite;
		if(!faceSprite.loadFromFile("data/imgs/"+faceName))
			std::cout << "error loading image "<< faceName << std::endl;
		faces[faceName] = faceSprite;
	}

	std::ifstream roomFin("data/rooms/rooms.txt");
	int numRooms;
	roomFin>>numRooms;
	std::map<std::string, Room*> rooms;
	for (int i = 0; i < numRooms; ++i) {
		std::string roomName;
		roomFin>>roomName;
		rooms[roomName] = new Room(roomName);
	}

	Player player(rooms["startRoom"]->getName(), username);
	Enemy testEnemy;
	BattleStats battleStats(player.getHealth(), testEnemy.getHealth());
	Dialogue dialogue;

	// super temporrary solution, the character shown needs to be given in the objects.json file for the room
	sf::Texture tmpFaceSprite;
	if(!tmpFaceSprite.loadFromFile("data/imgs/dog.png"))
		std::cout << "error loading image" << std::endl;
	dialogue.setSpriteTexture(&tmpFaceSprite);
	battleStats.setEnemyFaceTexture(&tmpFaceSprite);
	battleStats.setPlayerFaceTexture(&tmpFaceSprite);

	HUD hud(username, player.getCurrentQuest()); 
	scaleViews(&window, &mainView, &dialogue, &hud, &battleStats);
	hud.setRoom(player.getCurRoom());
	if(player.questCompleted())
		player.updateQuest();

	sf::Vector2f cameraPos;
	cameraPos.x = 0; cameraPos.y = 0;

	bool playSound = false;
	if (playSound){
		sf::Music music;
		music.openFromFile("data/song.ogg");
		music.play();
		music.setLoop(true);
	}

	std::cout << "starting game loop" << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
			else if (event.type == sf::Event::Resized) {
				scaleViews(&window, &mainView, &dialogue, &hud, &battleStats);
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Q){
					window.close();
					std::cout << "no seg faults yet..." << std::endl;
					return 0;
				}
				else if(event.key.code == sf::Keyboard::C)
					dialogue.setOpenState(false);
				else if(event.key.code == sf::Keyboard::B) // for debugging ONLY
					battleMode = true;
				else if(event.key.code == sf::Keyboard::N) // for debugging ONLY
					battleMode = false;
				else if(event.key.code == sf::Keyboard::Space){
					if(player.attackReady()){
						player.launchAttack();
					}
				}
			}
		}

		if(player.positionsSynced() && !player.shootingProjectile()){
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
				if(!rooms[player.getCurRoom()]->collidesWithObstacles(proposedPos))
					player.setPos(proposedPos.x, proposedPos.y);
			}
		}

		updateCameraPos(&cameraPos, player.getDrawPos(), rooms[player.getCurRoom()]->getDimensions());
		mainView.setCenter(cameraPos);
        window.clear(BLACK);
		window.setView(mainView);

		rooms[player.getCurRoom()]->draw(&window, &faces, battleMode);
		rooms[player.getCurRoom()]->handleObjectCollisions(&player, &dialogue, &hud, &faces, &battleMode);
		player.draw(&window);
		player.drawArrow(&window);

		if(battleMode){
			if(testEnemy.isDead()){ // this is bad, is it even safe????
				testEnemy.setHealth(10);
			}
			player.handleProjectileCollisions(&testEnemy, &battleStats, "enemy");
			testEnemy.handleProjectileCollisions(&player, &battleStats, "player");
			testEnemy.draw(&window);
			if(testEnemy.positionsSynced() && !testEnemy.shootingProjectile())
				testEnemy.wander(rooms[player.getCurRoom()]->getDimensions());
			if(player.isDead() || testEnemy.isDead()){
				battleMode = false;
				dialogue.setOpenState(false);
			}
			battleStats.draw(&window);
		}
		else{ // normalMode
			if(dialogue.isOpen())
				dialogue.draw(&window);
		}
		hud.draw(&window);
        window.display();
    }
    return 0;
}

