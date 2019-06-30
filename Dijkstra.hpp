#ifndef DIJKSTRA_H
#define DIJKSTRA_H value
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "SFML/Graphics.hpp"

class Dijkstra{
	private: 
		int** baseGraph;
		int** specificGraph; // specific graph adds a vertex that is the start location and a vertex that is the end location
		json teleporterIdxConversion;
	 	int teleporterCt;

		int taxicabDist(int x0, int y0, int x1, int y1);
		void setSpecificGraph(sf::Vector2i startPos, std::string startRoom, sf::Vector2i endPos, std::string endRoom);
		int findPath();
	public:
		Dijkstra();
		int getOptimalPath(sf::Vector2i startPos, std::string startRoom, sf::Vector2i endPos, std::string endRoom);
};
#endif /* ifndef DIJKSTRA_H */
