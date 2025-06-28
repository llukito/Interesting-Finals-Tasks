#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include "lexicon.h"
#include "shortest_path.h"
#include "max_weight.h"


using namespace std;

void printTestResults(bool passed, int & testNum, int & passedCounter) {
	testNum++;
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	} else {
		cout << "test " << testNum << " failed" << endl;
	}
}

void readGridFromFile(string fileName, Grid<int> &grid, int &answ) {
	ifstream file;
	file.open(fileName.c_str());
	int n, m;
	file >> n >> m >>  answ;
	grid.resize(n, m);
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			file >> grid[i][j];
		}
	}
	file.close();
}

void writeWeightsTestToFile(string fileName, Vector<int> &weights, 
								  Vector<int> &items, int answ) {
	ofstream file;
	file.open(fileName.c_str());
	file << weights.size() << " " << items.size() << " " << answ << endl;
	for (int i=0; i<weights.size(); i++) {
		file << weights[i] << " ";
	}
	file << endl;
	for (int i=0; i<items.size(); i++) {
		file << items[i] << " ";
	}
	file << endl;

	file.close();
}

void generateWightsTests() {
	for (int i=1; i<=50; i++) {
		Vector<int> weights;
		Vector<int> items;
		string name = "weights\\test" + integerToString(i) + ".txt"; 
		int numWeights = randomInteger(7, 10);
		int numItems = randomInteger(7, 15);
		for (int i=0; i<numWeights; i++) {
			weights.add(randomInteger(1, 80));	
		}
		for (int i=0; i<numItems; i++) {
			items.add(randomInteger(1, 500));	
		}
		int res = maxWeight(weights, items);
		writeWeightsTestToFile(name, weights, items, res);
	}
}

void readWeightsTestFromFile(string fileName, Vector<int> &weights, 
								  Vector<int> &items, int &answ) {
	ifstream file;
	file.open(fileName.c_str());
	int numWeights, numItems;
	file >> numWeights >> numItems >> answ;
	for (int i=0; i<numWeights; i++) {
		int w;
		file >> w;
		weights.add(w);
	}
	for (int i=0; i<numItems; i++) {
		int w;
		file >> w;
		items.add(w);
	}

	file.close();
}
void writeShortestPathTestToFile(string fileName, Grid<int> &table, int answ) {
	ofstream file;
	file.open(fileName.c_str());
	file << table.numRows() << " " << table.numCols() << " " << answ << endl;

	for (int row=0; row<table.numRows(); row++) {
		for (int col=0; col<table.numCols(); col++) {
			file << table[row][col] << " ";
		}	
		file << endl;
	}
	file.close();
}

void runShortestPathTests() {
	cout << "Run Shortest Path tests" << endl;
	int testNum = 0;
	int passedCounter = 0;
	bool passed;
	int num = 50;
	Grid<int> table;
	int answ;
	for (int i=1; i<=num; i++) {
		readGridFromFile("path\\test" + integerToString(i) + ".txt", table, answ);
		int res = getShortestPath(table);
		cout << res << " " << answ << endl;
		printTestResults(res == answ, testNum, passedCounter);
	}

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

void runMaxWeightRandomTests() {
	cout << "Run Max Weights tests" << endl;
	int testNum = 0;
	int passedCounter = 0;
	for (int i=1; i<=60; i++) {
		Vector<int> weights;
		Vector<int> items;
		int answ;
		string name = "weights\\test (" + integerToString(i) + ").txt"; 
		readWeightsTestFromFile(name, weights, items, answ);
		int res = maxWeight(weights, items);
		printTestResults(res == answ, testNum, passedCounter);
	}
	cout << "###### passed " << passedCounter << " tests ######" << endl;
}


void runMaxWeightManualTests() {
	int testNum = 0;
	int passedCounter = 0;
	bool passed;
	Vector<int> weights;
	Vector<int> items;
	int res;

	weights += 3, 5;
	items += 3,5,7,8;
	res = maxWeight(weights, items);
	printTestResults(res == 13, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 1, 1, 1, 7;
	items += 3, 3, 12;
	res = maxWeight(weights, items);
	printTestResults(res == 15, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 1, 1, 1, 7, 8;
	items += 3, 3, 12, 17;
	res = maxWeight(weights, items);
	printTestResults(res == 29, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 1, 1, 1, 7, 8;
	items += 25, 20, 45, 60, 60;
	res = maxWeight(weights, items);
	printTestResults(res == 0, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 3, 10, 4;
	items += 1, 9, 20;
	res = maxWeight(weights, items);
	printTestResults(res == 29, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 3, 5;
	items += 3,5,6,8;
	res = maxWeight(weights, items);
	printTestResults(res == 14, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 3, 5, 29;
	items += 3,5,6,8,31,47,52,100;
	res = maxWeight(weights, items);
	printTestResults(res == 83, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 3,5,29,70,35,30,10;
	items += 3,5,6,8,31,47,52,100;
	res = maxWeight(weights, items);
	printTestResults(res == 152, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 3,5,29,35,30,10;
	items += 3,5,6,8,31,47,52,152,350;
	res = maxWeight(weights, items);
	printTestResults(res == 99, testNum, passedCounter);

	weights.clear();
	items.clear();
	weights += 1,13,5,29,35,30,10,100,98,198,298;
	items += 6,8,31,47,52,152,350,1800,500,400;
	res = maxWeight(weights, items);
	printTestResults(res == 900, testNum, passedCounter);

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

int main() {
	setRandomSeed(0);
	//generateWightsTests();
	runMaxWeightRandomTests();
	//runMaxWeightManualTests();

	//generateShortestPathTests();
	//runShortestPathTests();
	return 0;
}