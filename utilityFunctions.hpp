#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
#include "Dialogue.hpp"
#include "HUD.hpp"
// float abs(float x);
int sgn(int x);
float mint(float x, float y);
float maxt(float x, float y);
void updateCameraPos(sf::Vector2f *cameraPos, sf::Vector2f userPos, sf::Vector2i roomDimensions);
bool tileHitsTile(sf::Vector2f posA, sf::Vector2f posB);
void scaleViews(sf::RenderWindow *window, sf::View *mainView, Dialogue *dialogue, HUD *hud);
#endif // UTILITY_FUNCTIONS_H
