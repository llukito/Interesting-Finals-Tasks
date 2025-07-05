#ifndef MyGrid_Included
#define MyGrid_Included

#include "console.h"
using namespace std;

class MyGrid {
public:
	MyGrid(int numRows, int numCols);
	int NumRows();
	int NumColumns();
	void SetValue(int i, int j, int value);
	int GetValue(int i, int j);
	void RemoveRow(int indx);
	void RemoveColumn(int indx);
	void InsertRow(int indx);
	void InsertColumn(int indx);


private:
	struct Cell {
		int value;
		Cell* up;
		Cell* down;
		Cell* right;
		Cell* left;
		Cell() {
			up = down = right = left = nullptr;
			value = 0;
		}
	};
	Cell* root;
	int rows;
	int cols;
};


#endif;