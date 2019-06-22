#ifndef BATTLE_STATS_H
#define BATTLE_STATS_H
#include "SFML/Graphics.hpp"
#include <map>
#include "TextDisplay.hpp"
class BattleStats : public TextDisplay {
	private:
		sf::Sprite playerFace, enemyFace;
		sf::Vertex battleStatsBackdrop[4];
	public:
		BattleStats();
		void draw(sf::RenderWindow *window);
		void setEnemyFaceTexture(sf::Texture *texture);
		void setPlayerFaceTexture(sf::Texture *texture);
};
#endif // BATTLE_STATS_H
