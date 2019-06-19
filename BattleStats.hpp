#ifndef BATTLE_STATS_H
#define BATTLE_STATS_H
#include <SFML/Graphics.hpp>
class BattleStats{
	private:
		const float TEXT_PADDING = 10.0f;
		const int TEXT_SIZE = 20;
		sf::View battleStatsView;
		sf::Font font;
		sf::Sprite playerFace, enemyFace;
		sf::Text playerHealth, playerAttack, enemyHealth, enemyAttack;
		sf::Vertex battleStatsBackdrop[4];
		void initializeText(sf::Text *text, float x, float y, std::string initString);
	public:
		BattleStats();
		void draw(sf::RenderWindow *window);
		void setBattleStatsViewViewport(sf::FloatRect viewport);
		void setEnemyFaceTexture(sf::Texture *texture);
		void setPlayerFaceTexture(sf::Texture *texture);
		void setViewport(sf::FloatRect viewport);
};
#endif // BATTLE_STATS_H
