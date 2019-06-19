
#include <SFML/Graphics.hpp>

#include "utilityFunctions.hpp"
#include "constants.hpp"

int sgn(int x){
	return (x>0) - (x<0);
}

float mint(float x, float y){
	return x > y ? y : x;
}

float maxt(float x, float y){
	return x < y ? y : x;
}

void updateCameraPos(sf::Vector2f *cameraPos, sf::Vector2f userPos, sf::Vector2i roomDimensions){
	cameraPos->x = userPos.x + TILE_WIDTH/2;
	if (cameraPos->x < SCREEN_DIMENSIONS.x/2)
		cameraPos->x = SCREEN_DIMENSIONS.x/2;
	if (cameraPos->x > roomDimensions.x*TILE_WIDTH - SCREEN_DIMENSIONS.x/2)
		cameraPos->x = roomDimensions.x*TILE_WIDTH - SCREEN_DIMENSIONS.x/2;

	cameraPos->y = userPos.y + TILE_WIDTH/2;
	if (cameraPos->y < SCREEN_DIMENSIONS.y/2)
		cameraPos->y = SCREEN_DIMENSIONS.y/2;
	if (cameraPos->y > roomDimensions.y*TILE_WIDTH - SCREEN_DIMENSIONS.y/2)
		cameraPos->y = roomDimensions.y*TILE_WIDTH - SCREEN_DIMENSIONS.y/2;
}

void scaleViews(sf::RenderWindow *window, sf::View *mainView, Dialogue *dialogue, HUD *hud, BattleStats *battleStats){
	float ratioX = window->getSize().x/SCREEN_DIMENSIONS.x;
	float ratioY = window->getSize().y/SCREEN_DIMENSIONS.y;
	if(ratioX < ratioY){
		float newRatioY = SCREEN_DIMENSIONS.y*ratioX/window->getSize().y;
		mainView->setViewport(sf::FloatRect(0.0,(1-newRatioY)*0.5f,1.0,newRatioY));
		dialogue->setDialogueViewViewport(sf::FloatRect(0.0,1.0-DIALOGUE_VIEWPORT_RELATIVE_HEIGHT*newRatioY-(1-newRatioY)*0.5f,1.0,DIALOGUE_VIEWPORT_RELATIVE_HEIGHT*newRatioY));
		hud->setViewport(sf::FloatRect(0.0,(1-newRatioY)*0.5f,1.0,HUD_VIEWPORT_RELATIVE_HEIGHT*newRatioY));
		battleStats->setViewport(sf::FloatRect(0.0,1.0-BATTLE_STATS_VIEWPORT_RELATIVE_HEIGHT*newRatioY-(1-newRatioY)*0.5f,1.0,BATTLE_STATS_VIEWPORT_RELATIVE_HEIGHT*newRatioY));
	}
	else{
		float newRatioX = SCREEN_DIMENSIONS.x*ratioY/window->getSize().x;
		mainView->setViewport(sf::FloatRect((1-newRatioX)*0.5f, 0.0f, newRatioX, 1.0f));
		dialogue->setDialogueViewViewport(sf::FloatRect((1-newRatioX)*0.5f,1.0-DIALOGUE_VIEWPORT_RELATIVE_HEIGHT,newRatioX,DIALOGUE_VIEWPORT_RELATIVE_HEIGHT)); // this draws from top left
		hud->setViewport(sf::FloatRect((1-newRatioX)*0.5f,0.0f,newRatioX,HUD_VIEWPORT_RELATIVE_HEIGHT));
		battleStats->setViewport(sf::FloatRect((1-newRatioX)*0.5f,1.0-BATTLE_STATS_VIEWPORT_RELATIVE_HEIGHT,newRatioX,BATTLE_STATS_VIEWPORT_RELATIVE_HEIGHT)); // this draws from top left
	}
}
