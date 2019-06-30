#include "Dijkstra.hpp"
#include <limits.h>
#include <queue>
#include <iostream>
#include <vector>
#include <assert.h>

// A distance of 0 indicates that it is impossible to travel directly from one vertex to another
// Note: there will be no self loops so A[i][i] = 0 allways
int getPath(int **dists, int n, int start, int end){
	int bestTeleporter = 0;
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
	// priority queue that compares sizes using the dists array
	std::priority_queue<int, std::vector<int>, decltype(compare)> nodesToCheck(compare); // need a custom function for comparisons
	nodesToCheck.push(start);
	
	while(!nodesToCheck.empty()){
		int cur = nodesToCheck.top();
		nodesToCheck.pop();
		std::cout << "Node: " << cur << std::endl;
		for(int i = 0; i < n; i++){// connections
			if(cur != i && dists[cur][i] != 0){
				int new_dist = dists[cur][i]+distsFromStart[cur];
				if(new_dist < distsFromStart[i]){
					distsFromStart[i] = new_dist;
					nodesToCheck.push(i);
					optimalPaths[i].clear();
					for (auto it = optimalPaths[cur].begin(); it != optimalPaths[cur].end(); it++) {
						std::cout << (*it) << std::endl;
						optimalPaths[i].push_back(*it);
					}
					optimalPaths[i].push_back(cur);
				}
			}
		}
	}

	int minDist = INT_MAX;
	int achieved = 0;
	for (int i = 0; i < n; i++) {
		std::cout << "distsFromStart["<<i<<"] = "<< distsFromStart[i] << std::endl;
		if (distsFromStart[i] < minDist){
			achieved = i;
			minDist = distsFromStart[i];
		}
	}

	std::cout << "optimal path" << std::endl;
	for(auto it = optimalPaths[end].begin(); it != optimalPaths[end].end(); it++){
		std::cout << (*it) << "->";
	}
	std::cout << end << std::endl;

	return bestTeleporter;
}

