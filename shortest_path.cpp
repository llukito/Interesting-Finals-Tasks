#include "shortest_path.h"
#include "queue.h"
#include "set.h"
#include "grid.h"
#include "unordered_set"

int getShortestPath(Grid<int> &table) {
	if (table.numRows() == 1 && table.numCols() == 1)return 0;
	int res = INT_MAX;
	Queue<pair<pair<int,int>, pair<int,int>>> q;
	unordered_set<int> visited;
	visited.insert(0);
	if (1 < table.numCols()) {
		if (table[0][1] > table[0][0]) {
			visited.insert(1);
			q.enqueue({ {0,1},{1,1} });
		}
		else if (table[0][1] < table[0][0]) {
			visited.insert(1);
			q.enqueue({ {0,1},{-1,1}});
		}
	}
	if (1 < table.numRows()) {
		if (table[1][0] > table[0][0]) {
			visited.insert(table.numCols());
			q.enqueue({ {1,0},{1,1} });
		}
		else if (table[1][0] < table[0][0]) {
			visited.insert(table.numCols());
			q.enqueue({ {1,0},{-1,1}});
		}
	}
	while (!q.isEmpty()) {
		pair<pair<int, int>, pair<int,int>> pr = q.dequeue();
		int r = pr.first.first; int c = pr.first.second;
		int inc = pr.second.first; int length = pr.second.second;
		if (r == table.numRows()-1 && c == table.numCols()-1) {
			return length;
		}
		// right
		if (c + 1 < table.numCols() && !visited.count(r * table.numCols() + c + 1)) {
			if (table[r][c + 1] > table[r][c]) {
				if (inc == 1) {
					visited.insert(r * table.numCols() + c + 1);
					q.enqueue({ {r,c + 1}, {inc, length + 1} });
				}
			}
			else if (table[r][c + 1] < table[r][c]) {
				if (inc == -1) {
					visited.insert(r * table.numCols() + c + 1);
					q.enqueue({ {r,c + 1}, {inc, length + 1} });
				}
			}
		}
		// left
		if (c - 1 >= 0 && !visited.count(r * table.numCols() + c - 1)) {
			if (table[r][c - 1] > table[r][c]) {
				if (inc == 1) {
					visited.insert(r * table.numCols() + c - 1);
					q.enqueue({ {r,c - 1}, {inc, length + 1} });
				}
			}
			else if (table[r][c - 1] < table[r][c]) {
				if (inc == -1) {
					visited.insert(r * table.numCols() + c - 1);
					q.enqueue({ {r,c - 1}, {inc, length + 1} });
				}
			}
		}
		// down
		if (r + 1 < table.numRows() && !visited.count((r + 1) * table.numCols() + c)) {
			if (table[r+1][c] > table[r][c]) {
				if (inc == 1) {
					visited.insert((r+1) * table.numCols() + c );
					q.enqueue({ {r+1,c}, {inc, length + 1} });
				}
			}
			else if (table[r+1][c] < table[r][c]) {
				if (inc == -1) {
					visited.insert((r+1) * table.numCols() + c);
					q.enqueue({ {r+1,c}, {inc, length + 1} });
				}
			}
		}
	}
	return  res != INT_MAX ? res : -1;
}
