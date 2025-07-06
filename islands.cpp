
#include "islands.h"
#include <iostream>
#include <vector.h>
#include <vector>
#include <set>
#include "unordered_set"

void fill(Grid<int>& grid2, unordered_set<int>& visited, vector < pair<int, int>>& currRoad, int row, int col) {
	visited.insert(row * grid2.numCols() + col);
	currRoad.push_back({ row, col });
	if (row + 1 < grid2.numRows() && grid2[row + 1][col] == 1 && !visited.count((row+1) * grid2.numCols() + col)) {
		fill(grid2, visited, currRoad, row + 1, col);
	}
	if (row - 1 >=0 && grid2[row - 1][col] == 1 && !visited.count((row - 1) * grid2.numCols() + col)) {
		fill(grid2, visited, currRoad, row - 1, col);
	}
	if (col + 1 < grid2.numCols() && grid2[row][col+1] == 1 && !visited.count((row) * grid2.numCols() + col+1)) {
		fill(grid2, visited, currRoad, row, col+1);
	}
	if (col - 1 >= 0 && grid2[row][col-1] == 1 && !visited.count((row) * grid2.numCols() + col-1)) {
		fill(grid2, visited, currRoad, row, col-1);
	}
}

bool valid(vector < pair<int, int>>& currRoad, Grid<int>& grid1) {
	for (pair<int, int> pr : currRoad) {
		if (grid1[pr.first][pr.second] != 1)return false;
	}
	return true;
}

int countSubIslands(Grid<int>& grid1, Grid<int>& grid2) {
	int res = 0;
	unordered_set<int> visited;
	for (int r = 0; r < grid2.numRows(); r++) {
		for (int c = 0; c < grid2.numCols(); c++) {
			int val = r * grid2.numCols() + c;
			if (grid2[r][c] == 1 && !visited.count(val)) {
				vector < pair<int, int>> currRoad;
				fill(grid2, visited, currRoad, r, c);
				if (valid(currRoad, grid1)) {
					res++;
				}
			}
		}
	}
	return res;
}

