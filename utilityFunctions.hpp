#ifndef UTILITY_FUNCTIONS
#define UTILITY_FUNCTIONS
#include "Dialogue.hpp"
float mint(float x, float y);
float maxt(float x, float y);
void updateCameraPos(sf::Vector2f *cameraPos, sf::Vector2f userPos);
bool tileHitsTile(sf::Vector2f posA, sf::Vector2f posB);
void scaleViews(sf::RenderWindow *window, sf::View *mainView, Dialogue *dialogue);
#endif // UTILITY_FUNCTIONS
