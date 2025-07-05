#include "NetworkDelayTime.h"
#include "unordered_map"
#include "pqueue.h"

int networkDelayTime(HashMap<int, Vector<Edge> >& graph, int n, int k) {
	unordered_map<int, int> dist;
	dist[k] = 0;
	PriorityQueue < pair<int, int>> pq;
	pq.enqueue({ k,0}, 0);
	cout << graph.size() << endl;
	while (!pq.isEmpty()) {
		pair<int, int> pr = pq.dequeue();
		int node = pr.first; int len = pr.second;
		if (dist.count(node)) {
			if (dist[node] < len) continue;
		}
		dist[node] = len;
		for (Edge ed : graph[node]) {
			if (!dist.count(ed.to)) {
				pq.enqueue({ ed.to, len + ed.time }, len+ed.time);
			}
			else if(dist[ed.to] > len + ed.time){
				pq.enqueue({ ed.to, len + ed.time }, len + ed.time);
			}
		}
	}
	if (dist.size() != n)return -1;
	int res = 0;
	for (auto& entry : dist) {
		res = max(entry.second, res);
	}
	return res;
}
