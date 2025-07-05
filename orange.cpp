#include "Orange.h"
#include <iostream>
#include "queue.h"

int orangesRotting(int** grid, int w, int h, int x, int y) {
	int oranges = 1;
	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {
			if (grid[r][c] == 1) {
				oranges++;
			}
		}
	}
	Queue<pair<int,int>> q;
	q.enqueue({ x,y });
	int res = 0;
	while (!q.isEmpty()) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			pair<int, int> pr = q.dequeue();
			int row = pr.first; int col = pr.second;
			oranges--;
			if (oranges == 0) {
				return res;
			}
			if (row + 1 < h && grid[row+1][col] == 1) {
				grid[row+1][col] = 2;
				q.enqueue({ row + 1, col });
			}
			if (row - 1 >=0 && grid[row - 1][col] == 1) {
				grid[row-1][col] = 2;
				q.enqueue({ row - 1, col });
			}
			if (col + 1 < w && grid[row ][col+1] == 1) {
				grid[row][col+1] = 2;
				q.enqueue({ row, col+1 });
			}
			if (col - 1 >=0 && grid[row][col-1] == 1) {
				grid[row][col-1] = 2;
				q.enqueue({ row, col-1 });
			}
		}
		res++;
	}
	return -1;
}