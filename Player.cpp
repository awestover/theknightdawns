
#include "Player.hpp"
#include "constants.hpp"

void Player::initialize() {
	pos.x = TILE_WIDTH; pos.y = TILE_WIDTH;
	dog_texture.loadFromFile("data/imgs/dog.png");
	dog_sprite.setTexture(dog_texture);
}

void Player::draw(sf::RenderWindow *window) {
	dog_sprite.setPosition(pos);
	window->draw(dog_sprite);
}

void Player::setPos(float xpos, float ypos){
	pos.x = xpos;
	pos.y = ypos;
}

sf::Vector2f Player::getPos(){
	return pos;
}
