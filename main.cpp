#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "MyGrid.h"


using namespace std;

void printTestResults(bool passed, int testNum, int& passedCounter) {
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	}
	else {
		cout << "test " << testNum << " failed" << endl;
	}
}

bool runGridTest(int testNum) {
	bool passed = 0;
	MyGrid* g;

	switch (testNum) {
	case 0:
		g = new MyGrid(30, 50);
		passed = g->NumRows() == 30 && g->NumColumns() == 50;
		break;
	case 1:
		g = new MyGrid(5, 2);
		g->SetValue(0, 1, 17);
		g->SetValue(3, 1, 19);
		passed = g->NumRows() == 5 && g->NumColumns() == 2 &&
			g->GetValue(0, 1) == 17 && g->GetValue(3, 1) == 19 &&
			g->GetValue(0, 0) == 0 && g->GetValue(1, 0) == 0 &&
			g->GetValue(1, 1) == 0 && g->GetValue(3, 0) == 0;
		break;
	case 2:
		g = new MyGrid(4, 1);
		g->SetValue(0, 0, 0);
		g->SetValue(2, 0, 30);
		g->SetValue(0, 0, 50);
		passed = g->NumRows() == 4 && g->NumColumns() == 1 &&
			g->GetValue(0, 0) == 50 && g->GetValue(2, 0) == 30 &&
			g->GetValue(1, 0) == 0 && g->GetValue(3, 0) == 0;
		break;
	case 3:
		g = new MyGrid(5, 3);
		g->RemoveColumn(2);
		g->RemoveColumn(1);
		passed = g->NumRows() == 5 && g->NumColumns() == 1;
		break;
	case 4:
		g = new MyGrid(9, 2);
		g->RemoveColumn(1);
		g->RemoveColumn(0);
		passed = g->NumRows() == 0 && g->NumColumns() == 0;
		break;
	case 5:
		g = new MyGrid(3, 6);
		g->RemoveRow(1);
		g->RemoveRow(1);
		passed = g->NumRows() == 1 && g->NumColumns() == 6;
		break;
	case 6:
		g = new MyGrid(2, 10);
		g->RemoveRow(1);
		g->RemoveRow(0);
		passed = g->NumRows() == 0 && g->NumColumns() == 0;
		break;
	case 7:
		g = new MyGrid(4, 2);
		g->SetValue(3, 1, 90);
		g->SetValue(3, 0, 50);
		g->SetValue(2, 0, 30);
		g->RemoveRow(2);
		passed = g->NumRows() == 3 && g->NumColumns() == 2 &&
			g->GetValue(2, 0) == 50 && g->GetValue(2, 1) == 90 &&
			g->GetValue(1, 0) == 0 && g->GetValue(1, 1) == 0;
		break;
	case 8:
		g = new MyGrid(4, 2);
		g->SetValue(3, 1, 90);
		g->SetValue(3, 0, 50);
		g->SetValue(2, 0, 30);
		g->RemoveRow(1);
		g->RemoveRow(1);
		passed = g->NumRows() == 2 && g->NumColumns() == 2 &&
			g->GetValue(1, 0) == 50 && g->GetValue(1, 1) == 90;
		break;
	case 9:
		g = new MyGrid(4, 2);
		g->SetValue(3, 1, 90);
		g->RemoveColumn(0);
		g->SetValue(3, 0, 50);
		g->SetValue(2, 0, 30);
		g->RemoveRow(1);
		g->RemoveRow(1);
		passed = g->NumRows() == 2 && g->NumColumns() == 1 &&
			g->GetValue(0, 0) == 0 && g->GetValue(1, 0) == 50;
		break;
	case 10:
		g = new MyGrid(1, 5);
		g->SetValue(0, 1, 70);
		g->SetValue(0, 2, 50);
		g->SetValue(0, 3, 10);
		g->RemoveColumn(0);
		g->SetValue(0, 1, 110);
		g->SetValue(0, 3, 130);
		passed = g->NumRows() == 1 && g->NumColumns() == 4 &&
			g->GetValue(0, 0) == 70 && g->GetValue(0, 1) == 110 &&
			g->GetValue(0, 2) == 10 && g->GetValue(0, 3) == 130;
		break;
	case 11:
		g = new MyGrid(7, 5);
		for (int i = 0; i < 5; i++) {
			g->SetValue(i, i, i * 10);
		}
		g->RemoveRow(1);
		g->RemoveColumn(1);
		passed = g->NumRows() == 6 && g->NumColumns() == 4 &&
			g->GetValue(0, 0) == 0 && g->GetValue(1, 1) == 20 &&
			g->GetValue(2, 2) == 30 && g->GetValue(3, 3) == 40;
		break;
	case 12:
		g = new MyGrid(7, 5);
		for (int i = 0; i < 5; i++) {
			g->SetValue(i, i, i);
		}
		g->RemoveRow(1);
		g->SetValue(2, 2, 220);
		g->RemoveColumn(1);
		g->SetValue(1, 1, 110);
		g->RemoveRow(0);

		passed = g->NumRows() == 5 && g->NumColumns() == 4 &&
			g->GetValue(0, 1) == 110 && g->GetValue(1, 1) == 220 &&
			g->GetValue(1, 2) == 3 && g->GetValue(2, 3) == 4;
		break;

	case 13:
		g = new MyGrid(3, 6);
		g->InsertRow(3);
		passed = g->NumRows() == 4 && g->NumColumns() == 6 &&
			g->GetValue(3, 0) == 0 && g->GetValue(3, 1) == 0;
		break;

	case 14:
		g = new MyGrid(1, 2);
		g->InsertColumn(2);
		passed = g->NumRows() == 1 && g->NumColumns() == 3 &&
			g->GetValue(0, 2) == 0;
		break;
	case 15:
		g = new MyGrid(2, 3);
		g->SetValue(0, 1, 1010);
		g->InsertColumn(1);
		passed = g->NumRows() == 2 && g->NumColumns() == 4 &&
			g->GetValue(0, 2) == 1010 && g->GetValue(0, 1) == 0 &&
			g->GetValue(1, 1) == 0;
		break;
	case 16:
		g = new MyGrid(7, 3);
		g->SetValue(3, 2, 1320);
		g->InsertRow(2);
		passed = g->NumRows() == 8 && g->NumColumns() == 3 &&
			g->GetValue(4, 2) == 1320 && g->GetValue(3, 2) == 0 &&
			g->GetValue(2, 0) == 0;
		break;
	case 17:
		g = new MyGrid(4, 2);
		g->SetValue(1, 1, 1110);
		g->SetValue(0, 1, 1010);
		g->InsertRow(1);
		g->SetValue(2, 1, 2210);
		g->SetValue(1, 1, 2110);
		g->InsertRow(0);
		passed = g->NumRows() == 6 && g->NumColumns() == 2 &&
			g->GetValue(0, 1) == 0 && g->GetValue(1, 1) == 1010 &&
			g->GetValue(2, 1) == 2110 && g->GetValue(3, 1) == 2210;
		break;
	case 18:
		g = new MyGrid(4, 2);
		g->SetValue(1, 1, 1110);
		g->SetValue(0, 0, 1000);
		g->InsertColumn(1);
		g->SetValue(2, 2, 2220);
		g->SetValue(1, 2, 2120);
		g->InsertColumn(3);
		g->SetValue(1, 3, 2130);
		passed = g->NumRows() == 4 && g->NumColumns() == 4 &&
			g->GetValue(0, 0) == 1000 && g->GetValue(1, 2) == 2120 &&
			g->GetValue(2, 2) == 2220 && g->GetValue(1, 3) == 2130 &&
			g->GetValue(0, 2) == 0 && g->GetValue(2, 3) == 0;
		break;
	case 19:
		g = new MyGrid(4, 3);
		g->SetValue(1, 2, 1120);
		g->SetValue(0, 1, 1010);
		g->InsertColumn(1);
		g->InsertRow(1);
		g->SetValue(2, 3, 2230);
		g->SetValue(1, 1, 2110);
		g->InsertRow(0);
		g->SetValue(1, 1, 3110);
		g->SetValue(1, 2, 3120);
		g->InsertRow(0);
		passed = g->NumRows() == 7 && g->NumColumns() == 4 &&
			g->GetValue(2, 1) == 3110 && g->GetValue(2, 2) == 3120 &&
			g->GetValue(3, 1) == 2110 && g->GetValue(4, 3) == 2230 &&
			g->GetValue(1, 1) == 0 && g->GetValue(3, 3) == 0;
		break;
	case 20:
		g = new MyGrid(4, 1);
		g->SetValue(0, 0, 100);
		g->SetValue(1, 0, 110);
		g->InsertColumn(0);
		g->SetValue(1, 1, 211);
		g->InsertColumn(1);
		g->SetValue(1, 2, 312);
		g->SetValue(1, 1, 311);
		g->InsertColumn(3);
		passed = g->NumRows() == 4 && g->NumColumns() == 4 &&
			g->GetValue(0, 1) == 0 && g->GetValue(1, 1) == 311 &&
			g->GetValue(1, 2) == 312 && g->GetValue(2, 1) == 0 &&
			g->GetValue(2, 2) == 0;
		break;
	case 21:
		g = new MyGrid(2, 1);
		g->SetValue(1, 0, 110);
		g->InsertColumn(0);
		g->SetValue(1, 1, 211);
		g->InsertColumn(0);
		g->SetValue(1, 2, 312);
		passed = g->NumRows() == 2 && g->NumColumns() == 3 &&
			g->GetValue(1, 0) == 0 && g->GetValue(1, 1) == 0 &&
			g->GetValue(1, 2) == 312 && g->GetValue(0, 0) == 0 &&
			g->GetValue(0, 1) == 0 && g->GetValue(0, 2) == 0;
		break;
	case 22:
		g = new MyGrid(1, 3);
		g->SetValue(0, 1, 101);
		g->SetValue(0, 2, 102);
		g->InsertRow(0);
		g->SetValue(1, 1, 211);
		g->SetValue(0, 2, 202);
		g->InsertRow(2);
		passed = g->NumRows() == 3 && g->NumColumns() == 3 &&
			g->GetValue(0, 1) == 0 && g->GetValue(1, 2) == 102 &&
			g->GetValue(1, 1) == 211 && g->GetValue(0, 2) == 202;
		break;
	case 23:
		g = new MyGrid(1, 3);
		g->SetValue(0, 1, 101);
		g->SetValue(0, 2, 102);
		g->InsertRow(0);
		g->SetValue(1, 1, 211);
		g->SetValue(0, 2, 202);
		g->RemoveRow(0);
		g->InsertRow(1);
		passed = g->NumRows() == 2 && g->NumColumns() == 3 &&
			g->GetValue(0, 1) == 211 && g->GetValue(0, 2) == 102 &&
			g->GetValue(0, 0) == 0;
		break;
	case 24:
		g = new MyGrid(2, 1);
		g->SetValue(1, 0, 1100);
		g->InsertColumn(0);
		g->SetValue(1, 1, 2110);
		g->InsertColumn(0);
		g->SetValue(1, 2, 3120);
		g->RemoveColumn(0);
		passed = g->NumRows() == 2 && g->NumColumns() == 2 &&
			g->GetValue(1, 0) == 0 && g->GetValue(1, 1) == 3120 &&
			g->GetValue(0, 0) == 0 && g->GetValue(0, 1) == 0;
		break;

	}

	return passed;
}

const int gridTestsNum = 25;

void runGridTests() {
	cout << "### Run Grid tests ###" << endl;
	int passedNum = 0;
	int testNum = 0;

	for (; testNum < gridTestsNum; testNum++) {
		bool res = runGridTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runGridTests();
	return 0;
}