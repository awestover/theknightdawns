#include "Animated.hpp"

// I don't like this; can't see a way to get around it though...
Animated::Animated(){
	visualDimensions.x = TILE_WIDTH; visualDimensions.y = TILE_WIDTH;
	texture.loadFromFile("data/imgs/dialoguePrompt.png");
	sprite.setTexture(texture);
	int numFramesWide = sprite.getLocalBounds().width/visualDimensions.x;
	numAniFrames = new int[1] {numFramesWide};
}

Animated::Animated(sf::Vector2i dimensions, std::string spritePath){
	visualDimensions.x = dimensions.x; visualDimensions.y = dimensions.x;
	texture.loadFromFile(spritePath);
	sprite.setTexture(texture);
	int numFramesWide = sprite.getLocalBounds().width/visualDimensions.x;
	numAniFrames = new int[1] {numFramesWide};
}

sf::Vector2f Animated::getDrawPos(){
	return draw_pos;
}

void Animated::changePos(int xpos, int ypos){
	draw_pos.x = TILE_WIDTH*xpos;
	draw_pos.y = TILE_WIDTH*ypos;
}

void Animated::draw(sf::RenderWindow *window) {
	sprite.setPosition(draw_pos.x - (visualDimensions.x - TILE_WIDTH)/2, draw_pos.y - (visualDimensions.y - TILE_WIDTH)/2);
	aniCt += 1;
	if(aniCt >= aniTurnOverCt){
		aniCt = 0;
		aniFrame = (aniFrame + 1) % numAniFrames[aniDirection];
	}
	if(visualDimensions.x == 75)
		std::cout << numAniFrames[aniDirection] << std::endl;
	sprite.setTextureRect(sf::IntRect(aniFrame*visualDimensions.x, aniDirection*visualDimensions.y, visualDimensions.x, visualDimensions.y));
	window->draw(sprite);
}
