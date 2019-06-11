
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

#include "Room.hpp"
#include "Dialogue.hpp"
#include "constants.hpp"
#include "utilityFunctions.hpp"

int main()
{
	bool dialogueOpen = false;
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

	sf::Texture rock_texture;
	rock_texture.loadFromFile("data/imgs/rock.png");
	sf::Sprite rock_sprite;
	rock_sprite.setTexture(rock_texture);

	rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));

	bool obstacles[NUM_TILES][NUM_TILES];
	std::ifstream fin("data/rooms/startRoom/obstacles.txt");
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			char cur;
			fin >> cur;
			if(cur == '1')
				obstacles[i][j] = true;
			else
				obstacles[i][j] = false;
		}
	}

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
						dialogueOpen = false;
				}
			}
		}

		updateCameraPos(&cameraPos, userPos);
		mainView.setCenter(cameraPos);

        window.clear(BLACK);
		window.setView(mainView);

		bg_sprite.setTextureRect(sf::IntRect(0, 0, WOLRD_DIMENSIONS.x, WOLRD_DIMENSIONS.y));
		window.draw(bg_sprite);

		// draw objects on top of background
		for(int i = 0; i < NUM_TILES; i++){
			for(int j = 0; j < NUM_TILES; j++){
				if(obstacles[i][j]){
					const sf::Vector2f cur_pos(TILE_WIDTH*j, TILE_WIDTH*i);
					rock_sprite.setPosition(cur_pos);
					window.draw(rock_sprite);
					if(tileHitsTile(cur_pos, dog_sprite.getPosition())){
						dialogueOpen = true;
						std::stringstream ss;
						ss<<"collision with: "<<i<<","<<j;
						dialogue.updateText(ss.str());
					}
				}
			}
		}
		window.draw(rock_sprite);

		dog_sprite.setPosition(userPos);
		window.draw(dog_sprite);

		if(dialogueOpen){
			dialogue.draw(&window);
		}

        window.display();
    }
    return 0;
}

