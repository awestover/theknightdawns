
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
using namespace std;

// PLZ DONT CHANGE THESE, the tilemap is 2048 by 2048 and 32*64=2048
const int NUM_TILES = 32;
const int TILE_WIDTH = 64;
const sf::Vector2f SCREEN_DIMENSIONS(800,600);
const sf::Vector2f WOLRD_DIMENSIONS(NUM_TILES*TILE_WIDTH, NUM_TILES*TILE_WIDTH);
const sf::Vector2f DIALOGUE_DIMENSIONS(SCREEN_DIMENSIONS.x, 100);
enum TILE_TYPES { EMPTY, WALL, OTHER };

bool dialogueOpen = false;
bool fullScreen = false;

float mint(float x, float y){
	return x > y ? y : x;
}
float maxt(float x, float y){
	return x < y ? y : x;
}

// template <typename T>
// sf::Rect<T>

bool tileHitsTile(sf::Vector2f posA, sf::Vector2f posB){
	bool xIn = mint(posA.x + TILE_WIDTH, posB.x + TILE_WIDTH) > maxt(posA.x, posB.x);
	bool yIn = mint(posA.y + TILE_WIDTH, posB.y + TILE_WIDTH) > maxt(posA.y, posB.y);
	return xIn && yIn;
}

void scaleMainView(sf::RenderWindow *window, sf::View *mainView){
	float rectWidth = SCREEN_DIMENSIONS.x/window->getSize().x;
	float rectHeight = SCREEN_DIMENSIONS.y/window->getSize().y;
	mainView->setViewport(sf::FloatRect((1-rectWidth)/2,(1-rectHeight)/2,rectWidth,rectHeight));
}

int main()
{
	sf::RenderWindow window;
	if(fullScreen){
		window.create(sf::VideoMode(NUM_TILES*TILE_WIDTH, NUM_TILES*TILE_WIDTH, 32), "RPG GAMMUUU!!", sf::Style::Fullscreen);
	}
	else {
		window.create(sf::VideoMode(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, 32), "RPG GAMMUUU!!");
	}
	window.setFramerateLimit(60);

	sf::View mainView;
	mainView.reset(sf::FloatRect(SCREEN_DIMENSIONS.x/2, SCREEN_DIMENSIONS.y/2, SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y));
	mainView.setViewport(sf::FloatRect(0.0, 0.0, 1.0, 1.0));
	scaleMainView(&window, &mainView);

	sf::View dialogueView(sf::FloatRect(DIALOGUE_DIMENSIONS.x/2, DIALOGUE_DIMENSIONS.y/2, DIALOGUE_DIMENSIONS.x, DIALOGUE_DIMENSIONS.y));
	dialogueView.setViewport(sf::FloatRect(0.0,0.8,1.0,0.2));

	// it'd be nice if this code all happened in a different file, or at least in a more organized fashion
	// maybe do a vector of textures and sprites?
	// Load images
	sf::Texture bg_texture;
	bg_texture.loadFromFile("data/tileMap.png");
	sf::Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);

	sf::Texture dog_texture;
	dog_texture.loadFromFile("data/dog.png");
	sf::Sprite dog_sprite;
	dog_sprite.setTexture(dog_texture);

	sf::Texture rock_texture;
	rock_texture.loadFromFile("data/rock.png");
	sf::Sprite rock_sprite;
	rock_sprite.setTexture(rock_texture);

	rock_sprite.setScale(TILE_WIDTH/(1.0*rock_sprite.getTextureRect().width), TILE_WIDTH/(1.0*rock_sprite.getTextureRect().height));

	sf::Font font;
	if(!font.loadFromFile("data/arial.ttf")){
		cout<<"error loading font"<<endl;
	}
	sf::Text dialogueText;
	dialogueText.setFont(font);
	dialogueText.setCharacterSize(TILE_WIDTH);
	dialogueText.setFillColor(sf::Color::Red);
	dialogueText.setPosition(DIALOGUE_DIMENSIONS.x/2, DIALOGUE_DIMENSIONS.y/2); // WHAT is this doing???

	sf::RectangleShape dialogueBackdrop(sf::Vector2f(DIALOGUE_DIMENSIONS.x, DIALOGUE_DIMENSIONS.y));
	dialogueBackdrop.setPosition(DIALOGUE_DIMENSIONS.x/2, DIALOGUE_DIMENSIONS.y/2); // are positions allways centers???????? does this mean my collision detection code is wrong?

	TILE_TYPES mapData[NUM_TILES][NUM_TILES];
	ifstream fin("data/map1.txt");
	for(int i = 0; i < NUM_TILES; i++){
		for(int j = 0; j < NUM_TILES; j++){
			char cur;
			fin >> cur;
			if(cur == 'e')
				mapData[i][j] = EMPTY;
			else if(cur == 'w')
				mapData[i][j] = WALL;
			else if(cur == 'o')
				mapData[i][j] = OTHER;
		}
	}

	sf::Vector2f cameraPos(0, 0);
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
				float rectWidth = SCREEN_DIMENSIONS.x/window.getSize().x;
				float rectHeight = SCREEN_DIMENSIONS.y/window.getSize().y;
				mainView.setViewport(sf::FloatRect((1-rectWidth)/2,(1-rectHeight)/2,rectWidth,rectHeight));
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
				}
			}
		}

		cameraPos.x = userPos.x + TILE_WIDTH/2;
		if (cameraPos.x < SCREEN_DIMENSIONS.x/2)
			cameraPos.x = SCREEN_DIMENSIONS.x/2;
		if (cameraPos.x > WOLRD_DIMENSIONS.x - SCREEN_DIMENSIONS.x/2)
			cameraPos.x = WOLRD_DIMENSIONS.x - SCREEN_DIMENSIONS.x/2;
		cameraPos.y = userPos.y + TILE_WIDTH/2;
		if (cameraPos.y < SCREEN_DIMENSIONS.y/2)
			cameraPos.y = SCREEN_DIMENSIONS.y/2;
		if (cameraPos.y > WOLRD_DIMENSIONS.y - SCREEN_DIMENSIONS.y/2)
			cameraPos.y = WOLRD_DIMENSIONS.y - SCREEN_DIMENSIONS.y/2;
		mainView.setCenter(cameraPos);

        window.clear(sf::Color(0, 0, 0, 1));
		window.setView(mainView);

		bg_sprite.setTextureRect(sf::IntRect(0, 0, WOLRD_DIMENSIONS.x, WOLRD_DIMENSIONS.y));
		window.draw(bg_sprite);

		// draw objects on top of background
		for(int i = 0; i < NUM_TILES; i++){
			for(int j = 0; j < NUM_TILES; j++){
				if(mapData[i][j] != EMPTY){
					const sf::Vector2f cur_pos(TILE_WIDTH*j, TILE_WIDTH*i);
					rock_sprite.setPosition(cur_pos);
					window.draw(rock_sprite);
					if(tileHitsTile(cur_pos, dog_sprite.getPosition())){
						dialogueOpen = true;
						stringstream ss;
						ss<<"collision with: "<<i<<","<<j;
						dialogueText.setString(ss.str());
					}
				}
			}
		}
		window.draw(rock_sprite);

		dog_sprite.setPosition(userPos);
		window.draw(dog_sprite);


		if(dialogueOpen){
			window.setView(dialogueView);
			window.draw(dialogueBackdrop);
			window.draw(dialogueText);
		}

        window.display();
    }
    return 0;
}

