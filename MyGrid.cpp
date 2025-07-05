#include "MyGrid.h"
#include <iostream>
using namespace std;

MyGrid::MyGrid(int numRows, int numCols) {
	rows = numRows;
	cols = numCols;
	root = NULL;
	for (int i = 0; i < numRows; i++) {
		Cell* row = NULL;
		for (int j = 0; j < numCols; j++) {
			Cell* newCell = new Cell;
			newCell->right = row;
			row = newCell;
		}
		row->down = root;
		root = row;
	}
}

int MyGrid::NumRows() {
	return rows;
}

int MyGrid::NumColumns() {
	return cols;
}

void MyGrid::SetValue(int i, int j, int value) {
	Cell* nd = root;
	for (int r = 0; r < i; r++) {
		nd = nd->down;
	}
	for (int c = 0; c < j; c++) {
		nd = nd->right;
	}
	nd->value = value;
}

int MyGrid::GetValue(int i, int j) {
	Cell* nd = root;
	for (int r = 0; r < i; r++) {
		nd = nd->down;
	}
	for (int c = 0; c < j; c++) {
		nd = nd->right;
	}
	return nd->value;
}

void MyGrid::RemoveRow(int indx) {
	if (indx == 0) {
		root = root->down;
	}
	else {
		Cell* prev = root;
		Cell* nd = root->down;
		for (int r = 1; r < indx; r++) {
			prev = nd;
			nd = nd->down;
		}
		prev->down = nd->down;
	}
	rows--;
	if (rows == 0) {
		cols = 0;
	}
}

void MyGrid::RemoveColumn(int indx) {
	if (indx == 0) {
		if (cols == 1) {
			root->right = nullptr;
			root->down = nullptr;
		}
		else {
			Cell* row = root;
			while (row->down) {
				row->right->down = row->down->right;
				row = row->down;
			}
			root = root->right;
		}
	}
	else {
		Cell* ss = root;
		while (ss) {
			Cell* nd = ss;

			Cell* prev = nd;
			Cell* temp = nd->right;
			int idx = 1;
			while (temp) {
				if (indx == idx) {
					prev->right = temp->right;
					break;
				}
				idx++;
				prev = temp;
				temp = temp->right;
			}
			ss = ss->down;
		}
	}
	cols--;
	if (cols == 0) {
		rows = 0;
	}
}

void MyGrid::InsertRow(int indx) {
	Cell* row = NULL;
	for (int j = 0; j < cols; j++) {
		Cell* newCell = new Cell;
		newCell->right = row;
		row = newCell;
	}
	if (indx == 0) {
		row->down = root;
		root = row;
	}
	else {
		Cell* prev = root;
		Cell* curr = root->down;
		int idx = 1;
		while (curr) {
			if (idx == indx) {
				row->down = curr;
				prev->down = row;
				break;
			}
			idx++;
			prev = curr;
			curr = curr->down;
			if (!curr) {
				prev->down = row;
				row->down = nullptr;
			}
		}
	}
	rows++;
}

void MyGrid::InsertColumn(int indx) {
	if (indx == 0) {
		Cell* temp = root;
		while (temp) {
			Cell* addable = new Cell();
			addable->right = temp->right;
			temp->right = addable;
			temp = temp->down;
		}

		temp = root;
		while (temp) {
			temp->right->value = temp->value;
			temp->value = 0;
			temp = temp->down;
		}
	}
	else {
		Cell* temp = root;
		while (temp) {
			Cell* prev = temp;
			Cell* curr = temp->right;
			int idx = 1;
			while (curr) {
				if (idx == indx) {
					Cell* addable = new Cell();
					addable->right = curr;
					prev->right = addable;
					break;
				}
				idx++;
				prev = curr;
				curr = curr->right;
				if (!curr) {
					Cell* addable = new Cell();
					prev->right = addable;
				}
			}

			temp = temp->down;
		}
	}
	cols++;
}

