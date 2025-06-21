#include <iostream>
#include <string>
#include "simpio.h"
#include "vector.h"
#include "console.h"
#include <time.h>
#include "allone.h"
#include "random.h"
#include "map.h"
#include "queue.h"


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

string* generateStrings(int n) {
	string* keys = new string[n];
	for (int i = 1; i < n; i++) {
		keys[i] = integerToString(i);
	}
	return keys;
}
const int n = 1000;
string* keys = generateStrings(n);

const int AllOneTestsNum = 30;

bool runAllOneSingleTest(int testNum) {
	bool passed = false;
	AllOne ao;
	switch (testNum) {
	case 1:
		passed = ao.getMaxKey() == "" && ao.getMinKey() == "";
		break;
	case 2:
		ao.inc("a");
		ao.inc("b");
		ao.inc("c");
		ao.inc("b");
		passed = ao.getMaxKey() == "b" && (ao.getMinKey() == "a" || ao.getMinKey() == "c");
		break;
	case 3:
		ao.inc("a");
		ao.inc("b");
		ao.inc("c");
		ao.inc("b");
		ao.inc("a");
		ao.inc("a");
		passed = ao.getMaxKey() == "a" && ao.getMinKey() == "c";
		break;
	case 4:
		ao.inc("a");
		ao.inc("b");
		ao.inc("a");
		ao.inc("d");
		ao.inc("b");
		ao.inc("b");
		passed = ao.getMaxKey() == "b" && ao.getMinKey() == "d";
		ao.inc("d");
		ao.inc("d");
		ao.inc("d");
		ao.inc("d");
		passed = passed && ao.getMaxKey() == "d" && ao.getMinKey() == "a";
		break;
	case 5:
		passed = true;
		for (int i = 1; i < 10; i++) {
			for (int k = 0; k < i; k++) {
				ao.inc(integerToString(i));
			}
			passed = passed && ao.getMaxKey() == integerToString(i) && ao.getMinKey() == "1";
		}
		for (int i = 0; i < 10; i++) {
			ao.inc("1");
		}
		passed = passed && ao.getMaxKey() == "1" && ao.getMinKey() == "2";
		for (int i = 0; i < 5; i++) {
			ao.inc("7");
			ao.inc("2");
		}
		passed = passed && ao.getMaxKey() == "7" && ao.getMinKey() == "3";
		break;
	case 6:
		ao.inc("a");
		ao.inc("b");
		ao.inc("a");
		ao.inc("c");
		ao.inc("b");
		ao.inc("b");
		passed = ao.getMaxKey() == "b" && ao.getMinKey() == "c";
		ao.inc("a");
		ao.inc("a");
		passed = passed && ao.getMaxKey() == "a" && ao.getMinKey() == "c";
		ao.dec("a");
		ao.dec("a");
		ao.dec("a");
		ao.dec("a");
		passed = passed && ao.getMaxKey() == "b" && ao.getMinKey() == "c";
		ao.dec("c");
		passed = passed && ao.getMaxKey() == "b" && ao.getMinKey() == "b";
		ao.dec("b");
		ao.dec("b");
		ao.dec("b");
		passed = passed && ao.getMaxKey() == "" && ao.getMinKey() == "";
		break;
	case 7:
		ao.inc("a");
		ao.inc("b");
		ao.inc("c");
		ao.inc("d");
		ao.inc("a");
		ao.inc("a");
		ao.inc("b");
		ao.inc("b");
		ao.inc("c");
		ao.inc("c");
		ao.dec("a");
		passed = (ao.getMaxKey() == "b" || ao.getMaxKey() == "c") && ao.getMinKey() == "d";
		ao.dec("a");
		ao.dec("b");
		ao.dec("c");
		ao.dec("c");
		ao.dec("d");
		ao.dec("a");
		passed = passed && ao.getMaxKey() == "b" && ao.getMinKey() == "c";		
		break;
		ao.dec("a");
	case 8:
		passed = true;
		for (int i = 1; i < 10; i++) {
			for (int k = 0; k < i; k++) {
				ao.inc(integerToString(i));
			}
			passed = passed && ao.getMaxKey() == integerToString(i);
			passed = passed && (i > 1 || ao.getMinKey() == integerToString(i-1));
		}
		passed = ao.getMaxKey() == "9" && ao.getMinKey() == "1";

		for (int i = 9; i > 1; i--) {
			for (int k = 0; k < i; k++) {
				ao.dec(integerToString(i));
			}
			passed = passed && ao.getMaxKey() == integerToString(i-1) && ao.getMinKey() == "1";
		}
		ao.dec("1");
		passed = passed && ao.getMaxKey() == "" && ao.getMinKey() == "";
		break;
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
		for (int i = 1; i < n; i++) {
			ao.inc(keys[i]);
		}
		passed = true;

		for (int i = 1; i < n; i++) {
			for (int k = 0; k < i; k++) {
				ao.inc(keys[i]);
			}
			passed = passed && ao.getMaxKey() == keys[i];
		}
		for (int i = 1; i < n-1; i++) {
			for (int k = 0; k < n-1; k++)
			ao.inc(keys[i]);
			passed = passed && ao.getMaxKey() == keys[i] && ao.getMinKey() == keys[i+1];
		}
		break;
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
		for (int i = 1; i < n; i++) {
			ao.inc(integerToString(i));
		}
		passed = true;

		for (int i = 1; i < n; i++) {
			for (int k = 0; k < i; k++) {
				ao.inc(keys[i]);
			}
			passed = passed && ao.getMaxKey() == keys[i];
		}

		for (int i = n-1; i > 1; i--) {
			for (int k = 0; k < i; k++) {
				ao.inc(keys[i]);
			}
			passed = passed && ao.getMaxKey() == keys[i-1];
		}

		passed = passed && ao.getMinKey() == "1";
		break;
	}

	return passed;
}

void runAllOneAllTests() {
	cout << "### Run AllOne tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum <= AllOneTestsNum; testNum++) {
		bool passed = runAllOneSingleTest(testNum);
		printTestResults(passed, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runAllOneAllTests();
	cout << "end" << endl;
	return 0;
}
