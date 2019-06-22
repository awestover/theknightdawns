#ifndef BATTLE_STATS_H
#define BATTLE_STATS_H
#include <map>
#include "TextDisplay.hpp"
class BattleStats : public TextDisplay {
	private:
		sf::Sprite playerFace, enemyFace;
		sf::Vertex battleStatsBackdrop[4];
	public:
		BattleStats(int playerHealth, int enemyHealth);
		void draw(sf::RenderWindow *window);
		void setEnemyFaceTexture(sf::Texture *texture);
		void setPlayerFaceTexture(sf::Texture *texture);
		void updateHealth(std::string whose, int playerHealth);
};
#endif // BATTLE_STATS_H
