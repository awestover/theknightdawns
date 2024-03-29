#include "Dijkstra.hpp"
#include <limits.h>
#include <queue>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <cstdlib>

Dijkstra::Dijkstra(){
	std::ifstream graphData("data/rooms/graph.json");
	json allGraphData;
	graphData >> allGraphData;
	teleporterCt = allGraphData["teleporterCt"];
	baseGraph = (int**)malloc(sizeof(int*)*teleporterCt);
	for (int i = 0; i < teleporterCt; i++) {
		baseGraph[i] = (int*)malloc(sizeof(int)*teleporterCt);
		for (int j = 0; j < teleporterCt; j++) {
			baseGraph[i][j] = allGraphData["graph"][i][j];
		}
	}
	specificGraph = (int**)malloc(sizeof(int*)*(teleporterCt+2));
	for (int i = 0; i < teleporterCt+2; i++) {
		specificGraph[i] = (int*)malloc(sizeof(int)*(teleporterCt+2));
		for (int j = 0; j < teleporterCt+2; j++) {
			specificGraph[i][j] = 0;
		}
	}
	teleporterIdxConversion = allGraphData["idxConversion"];
}

// A distance of 0 indicates that it is impossible to travel directly from one vertex to another
// Note: there will be no self loops so A[i][i] = 0 allways
int Dijkstra::findPath(){
	int n = teleporterCt + 2;
	int start = 0;
	int end = teleporterCt + 1;

	std::vector<int> optimalPaths[n];
	for (int i = 0; i < n; i++) {
		assert(optimalPaths[i].size() == 0);
	}
	int *distsFromStart = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		distsFromStart[i] = INT_MAX;
	}
	distsFromStart[start] = 0;
	// lambda function with ability to access local vars
	auto compare = [&](int lhs, int rhs) {
		return distsFromStart[lhs] < distsFromStart[rhs];
	};
	// priority queue that compares sizes using the distsFromStart array
	std::priority_queue<int, std::vector<int>, decltype(compare)> nodesToCheck(compare); // need a custom function for comparisons
	nodesToCheck.push(start);
	
	while(!nodesToCheck.empty()){
		int cur = nodesToCheck.top();
		nodesToCheck.pop();
		for(int i = 0; i < n; i++){// connections
			if(cur != i && specificGraph[cur][i] != 0){
				int new_dist = specificGraph[cur][i]+distsFromStart[cur];
				if(new_dist < distsFromStart[i]){
					distsFromStart[i] = new_dist;
					nodesToCheck.push(i);
					optimalPaths[i].clear();
					for (auto it = optimalPaths[cur].begin(); it != optimalPaths[cur].end(); it++) {
						optimalPaths[i].push_back(*it);
					}
					optimalPaths[i].push_back(cur);
				}
			}
		}
	}

	// std::cout << "optimal path" << std::endl;
	// for(auto it = optimalPaths[end].begin(); it != optimalPaths[end].end(); it++){
	//     std::cout << (*it) << "->";
	// }
	// std::cout << end << std::endl;
	// std::cout << "optimal path" << std::endl;
	// std::cout << "start->";
	// for(auto it = optimalPaths[end].begin()+1; it != optimalPaths[end].end(); it++){
	//     std::cout << teleporterIdxConversion[(*it)-1]["room"] << "->";
	// }
	// std::cout << "end" << std::endl;
	// std::cout << "end: " << optimalPaths[end][1] << std::endl;

	return optimalPaths[end][1]-1;
}

int Dijkstra::taxicabDist(int x0, int y0, int x1, int y1){
	return abs(x0-x1) + abs(y0-y1);
}

void Dijkstra::setSpecificGraph(sf::Vector2i startPos, std::string startRoom, sf::Vector2i endPos, std::string endRoom) {
	for (int i = 1; i < teleporterCt+1; i++) {
		for (int j = 1; j < teleporterCt+1; j++) {
			specificGraph[i][j] = baseGraph[i-1][j-1];
		}
	}
	// note: I'm intentionally only adding edges 1 way here: even though I guess you could technically return to start you never will
	for (int i = 0; i < teleporterCt; i++) {
		if(teleporterIdxConversion[i]["room"] == startRoom){
			specificGraph[0][i+1] = taxicabDist(startPos.x, startPos.y, teleporterIdxConversion[i]["pos"][0], teleporterIdxConversion[i]["pos"][1]);
		}
		if(teleporterIdxConversion[i]["room"] == endRoom){
			specificGraph[i+1][teleporterCt+1] = taxicabDist(teleporterIdxConversion[i]["pos"][0], teleporterIdxConversion[i]["pos"][1], endPos.x, endPos.y);
		}
	}
}

sf::Vector2f Dijkstra::getOptimalPath(sf::Vector2i startPos, std::string startRoom, sf::Vector2i endPos, std::string endRoom){
	setSpecificGraph(startPos, startRoom, endPos, endRoom);
	int firstPoint = findPath();
	int goalX = teleporterIdxConversion[firstPoint]["pos"][0];
	int goalY = teleporterIdxConversion[firstPoint]["pos"][1];
	sf::Vector2f delta(goalX-startPos.x, goalY-startPos.y);
	float mag = sqrt(delta.x*delta.x+delta.y*delta.y);
	if(mag!=0){
		delta.x /= mag;
		delta.y /= mag;
	}
	return delta;
}

