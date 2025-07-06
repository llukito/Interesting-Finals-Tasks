#include "shortest_path.h"
#include "queue.h"
#include "set.h"
#include "grid.h"
#include "vector"

int getShortestPath(Grid<int>& table) {
	if (table.numRows() <= 1 && table.numCols() <= 1)return 0;
	Queue<tuple<int,int, int>> q;
	if (table.numRows() > 1) {
		if (table[1][0] > table[0][0]) {
			q.enqueue({ 1,0,1 });
		}
		else if (table[1][0] < table[0][0]) {
			q.enqueue({ 1,0,-1 });
		}
	}
	if (table.numCols() > 1) {
		if (table[0][1] > table[0][0]) {
			q.enqueue({ 0,1,1 });
		}
		else if (table[0][1] < table[0][0]) {
			q.enqueue({ 0,1,-1 });
		}
	}
	int res = 1;
	vector<vector<bool>> visited(table.numRows(), vector<bool>(table.numCols(), false));
	visited[0][0] = true;
	while (!q.isEmpty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			auto tup = q.dequeue();
			int row = get<0>(tup); int col = get<1>(tup); int dir = get<2>(tup);
			if (visited[row][col])continue;
			visited[row][col] = true;
			if (row == table.numRows() - 1 && col == table.numCols() - 1)return res;
			if (row + 1 < table.numRows()) {
				if (dir == 1) {
					if (table[row + 1][col] > table[row][col]) {
						q.enqueue({ row + 1, col, 1 });
					}
				}
				else {
					if (table[row + 1][col] < table[row][col]) {
						q.enqueue({ row + 1, col, -1 });
					}
				}
			}
			if (col + 1 < table.numCols()) {
				if (dir == 1) {
					if (table[row][col+1] > table[row][col]) {
						q.enqueue({ row, col+1, 1 });
					}
				}
				else {
					if (table[row][col+1] < table[row][col]) {
						q.enqueue({ row, col+1, -1 });
					}
				}
			}
			if (col - 1 >=0) {
				if (dir == 1) {
					if (table[row][col - 1] > table[row][col]) {
						q.enqueue({ row, col - 1, 1 });
					}
				}
				else {
					if (table[row][col - 1] < table[row][col]) {
						q.enqueue({ row, col - 1, -1 });
					}
				}
			}
		}
		res++;
	}
	return -1;
}
