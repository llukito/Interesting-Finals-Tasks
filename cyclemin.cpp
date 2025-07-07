#include "cyclemin.h"
#include "unordered_map"
#include "unordered_set"

bool dfs(int node, int parent, unordered_set<int>& visited, unordered_map<int, vector<int>>& graph) {
	visited.insert(node);
	for (int nei : graph[node]) {
		if (!visited.count(nei)) {
			if (dfs(nei, node, visited, graph)) {
				return true;
			}
		}
		else if (nei != parent) {
			return true;
		}
	}
	return false;
}

bool valid(Vector<edgeT*>& g) {
	unordered_map<int, vector<int>> graph;
	for (edgeT* ed : g) {
		graph[ed->from].push_back(ed->to);
		graph[ed->to].push_back(ed->from);
	}
	unordered_set<int> visited;
	for (auto& entry : graph) {
		if (!visited.count(entry.first)) {
			if (dfs(entry.first, -1, visited, graph)) {
				return true;
			}
		}
	}
	return false;
}

int removeCycleMin(Vector<edgeT*>& g) {
	int minWeight = INT_MAX;
	for (int i = 0; i<g.size(); i++) {
		edgeT* temp = g[i];
		g[i] = g[g.size() - 1];
		g[g.size() - 1] = temp;
		g.remove(g.size() - 1);
		if (!valid(g)) {
			minWeight = min(temp->weight, minWeight);
		}
		g.push_back(temp);
		g[g.size() - 1] = g[i];
		g[i] = temp;
	}
	return minWeight != INT_MAX ? minWeight : -1;
}