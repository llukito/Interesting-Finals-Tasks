#include <fstream>
#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include "mapcount.h"
#include "random.h"
#include "map.h"

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

string getRandomString(int num, string symbols) {
	string res = "";
	for (int i = 0; i < num; i++) {
		res += symbols[randomInteger(0, symbols.size() - 1)];
	}
	return res;
}

void addRandomStrings(MapCount* mc, int num, int keyMaxSize, string prefix, string symbols, Map<string, int>* clone) {
	for (int i = 0; i < num; i++) {
		int keySize = randomInteger(1, keyMaxSize);
		string key = getRandomString(keySize, symbols);
		int val = randomInteger(1, 100);
		mc->add(key, val);
		if (clone != NULL) {
			clone->put(key, val);
		}
	}
	// cout << "after add: " << clone->toString() << endl;
}

void removeRandomStrings(MapCount* mc, int num, int keyMaxSize, string prefix, string symbols, Map<string, int>* clone) {
	for (int i = 0; i < num; i++) {
		int keySize = randomInteger(1, keyMaxSize);
		string key = getRandomString(keySize, symbols);
		mc->remove(key);
		if (clone != NULL) {
			clone->remove(key);
		}
	}
	// cout << "after remove: " << clone->toString() << endl;
}

bool isCorrect(MapCount* mc, Map<string, int> clone) {
	Vector<string> keys;
	foreach(string key in clone) {
		keys.add(key);
	}
	// cout << clone.toString() << endl;
	foreach(string key in keys) {
		for (int i = 0; i < key.size(); i++) {
			string prefix = key.substr(0, i + 1);
			int evenCount = mc->countEven(prefix);

			int count = 0;
			for (int j = 0; j < keys.size(); j++) {
				string k = keys[j];
				if (clone.containsKey(k) && k.find(prefix) == 0 && clone[k] % 2 == 0) {
					count++;
				}
			}
			if (evenCount != count) {
				return false;
			}
		}
	}
	return true;
}

const int MAP_SUM_TEST_NUM = 65;
const int MAP_ANSW[45][10] = {
	{5, 6, 27, 1, 1641, 0, 2, 0, 70, 5},
	{0, 197, 183, 0, 77, 170, 19, 200, 55, 1603},
	{538, 25, 2, 0, 1, 6, 6, 66, 180, 180},
	{2, 158, 12, 8, 2, 67, 15, 1, 6, 0},
	{175, 179, 51, 0, 1, 0, 1592, 1, 0, 173},
	{4, 165, 179, 0, 543, 197, 58, 197, 174, 0},
	{17, 1637, 0, 0, 3, 0, 194, 1656, 14, 0},
	{51, 579, 52, 9, 1, 16, 1, 0, 0, 190},
	{3, 170, 57, 159, 559, 1, 0, 167, 72, 23},
	{24, 1, 544, 0, 3, 1662, 0, 0, 181, 555},
	{19, 0, 4, 1, 48, 1676, 0, 55, 547, 4},
	{21, 16, 1598, 187, 0, 17, 1612, 5, 0, 1726},
	{8, 11, 56, 78, 62, 1667, 0, 540, 0, 3},
	{54, 7, 4, 0, 13, 7, 169, 0, 189, 17},
	{548, 59, 6, 8, 1645, 51, 0, 17, 25, 61},
	{0, 1, 174, 562, 0, 14, 546, 60, 0, 0},
	{4, 0, 16, 2, 11, 0, 1, 191, 0, 0},
	{56, 1702, 191, 530, 0, 590, 1, 67, 6, 551},
	{3, 0, 1660, 207, 1626, 182, 61, 16, 182, 8},
	{6, 1, 9, 16, 1, 1667, 11, 0, 520, 4},
	{190, 5, 2, 6, 3, 2, 538, 24, 0, 0},
	{0, 525, 17, 539, 62, 8, 525, 1666, 47, 1},
	{1635, 1644, 9, 61, 0, 10, 547, 11, 23, 0},
	{10, 0, 63, 584, 10, 14, 1, 6, 0, 15},
	{6, 1, 60, 0, 182, 1651, 9, 0, 1, 552},
	{0, 1, 0, 30, 9, 60, 0, 17, 569, 30},
	{2, 564, 204, 22, 63, 52, 0, 185, 1, 3},
	{1633, 7, 1, 564, 0, 1, 60, 1633, 5, 0},
	{67, 54, 1, 183, 52, 0, 0, 67, 64, 0},
	{0, 524, 23, 0, 5, 65, 15, 0, 4, 22},
	{183, 0, 1654, 0, 18, 2, 17, 0, 23, 544},
	{62, 0, 59, 192, 191, 0, 19, 19, 546, 1},
	{185, 1673, 1, 553, 1661, 2, 2, 565, 576, 8},
	{0, 158, 201, 0, 192, 0, 0, 0, 172, 0},
	{28, 552, 174, 542, 17, 1, 0, 1, 18, 174},
	{60, 0, 20, 0, 4, 187, 186, 1, 1585, 64},
	{0, 6, 155, 0, 188, 63, 0, 69, 7, 1},
	{1583, 1, 1, 1609, 0, 0, 0, 1, 1583, 560},
	{551, 0, 53, 60, 577, 20, 559, 0, 0, 2},
	{2, 510, 579, 1613, 6, 28, 1, 0, 0, 6},
	{0, 8, 5, 1, 0, 184, 0, 0, 61, 534},
	{0, 1621, 1, 1674, 531, 57, 0, 549, 1617, 0},
	{50, 2, 169, 7, 1611, 512, 1704, 0, 574, 52},
	{0, 557, 52, 2, 0, 1, 16, 546, 0, 0},
	{0, 572, 9, 1626, 46, 157, 1, 176, 0, 1702}
};
//ofstream outp("answ.txt");

bool runMapSumTest(int testNum) {
	bool passed = false;
	MapCount* map = new MapCount();

	switch (testNum) {
	case 1:
		map->add("t", 6);
		map->add("tbc", 2);
		map->add("bc", 4);
		passed = map->size() == 3 && map->countEven("t") == 2 &&
			map->countEven("tb") == 1 && map->countEven("bc") == 1;
		break;
	case 2:
		map->add("t", 1);
		map->add("tttt", 2);
		map->add("tbcd", 4);
		map->add("tbtcd", 6);
		passed = map->size() == 4 && map->countEven("t") == 3 &&
			map->countEven("tt") == 1 && map->countEven("tb") == 2 &&
			map->countEven("tbc") == 1 && map->countEven("tbt") == 1;
		break;
	case 3:
		map->add("t", 0);
		map->add("tt", 1);
		map->add("tttt", 2);
		map->add("tttttt", 4);
		map->add("tttttttt", 7);
		map->add("tttttttttt", 8);
		map->add("bb", 8);
		map->add("bbbb", 3);
		passed = map->size() == 8 && map->countEven("t") == 4 &&
			map->countEven("tt") == 3 && map->countEven("ttt") == 3 &&
			map->countEven("tttt") == 3 && map->countEven("ttttt") == 2 &&
			map->countEven("ttttttt") == 1 && map->countEven("b") == 1;
		break;
	case 4:
		map->add("t", 0);
		map->add("b", 1);
		map->add("c", 5);
		map->add("d", 0);
		passed = map->size() == 4 && map->countEven("t") == 1 &&
			map->countEven("b") == 0 && map->countEven("c") == 0 &&
			map->countEven("d") == 1;

		map->add("t", 2);
		map->add("b", 3);
		map->add("c", 8);
		map->add("d", 3);
		passed = map->size() == 4 && map->countEven("t") == 1 &&
			map->countEven("b") == 0 && map->countEven("c") == 1 &&
			map->countEven("d") == 0 && passed;
		break;
	case 5:
		map->add("t", 0);
		map->add("b", 1);
		map->add("c", 2);
		map->add("d", 4);
		map->add("tt", 5);
		map->add("tb", 8);
		map->add("tc", 9);
		map->add("bt", 4);
		map->add("btcd", 6);
		passed = map->size() == 9 && map->countEven("t") == 2 &&
			map->countEven("b") == 2 && map->countEven("c") == 1 &&
			map->countEven("d") == 1;

		map->add("bt", 11);
		map->add("tc", 12);
		map->add("tt", 2);
		map->add("t", 10);
		passed = map->size() == 9 && map->countEven("t") == 4 &&
			map->countEven("b") == 1 && map->countEven("c") == 1 &&
			map->countEven("d") == 1 && passed;
		break;
	case 6:
		map->add("t", 0);
		map->add("tbtb", 1);
		map->add("tc", 2);
		map->add("ztc", 4);
		map->add("tzt", 7);
		map->add("tztb", 8);
		map->add("bz", 8);
		map->add("bt", 3);
		passed = map->size() == 8 && map->countEven("t") == 3 &&
			map->countEven("tt") == 0 && map->countEven("tb") == 0 &&
			map->countEven("tz") == 1 && map->countEven("b") == 1 &&
			map->countEven("tzt") == 1 && map->countEven("zt") == 1;
		break;
	case 7:
		map->add("t", 6);
		map->add("tbc", 2);
		map->add("b", 4);
		map->remove("tbc");
		map->remove("tbc");
		passed = map->size() == 2 && map->countEven("t") == 1 &&
			map->countEven("b") == 1;
		break;
	case 8:
		map->add("t", 6);
		map->add("tbc", 2);
		map->add("tbb", 4);
		map->add("tbbcde", 8);
		map->add("tbbcdtf", 3);
		map->remove("tbbc");
		passed = map->size() == 5 && map->countEven("t") == 4 &&
			map->countEven("b") == 0 && map->countEven("tbbc") == 1;
		map->remove("tbb");
		passed = passed && map->size() == 4 &&
			map->countEven("t") == 3 && map->countEven("tbb") == 1;
		map->remove("tbbcde");
		passed = passed && map->size() == 3 && map->countEven("tbb") == 0;
		break;
	case 9:
		map->add("t", 6);
		map->add("ttttttb", 2);
		map->add("ttt", 4);
		map->add("ttt", 1);
		passed = map->size() == 3 && map->countEven("t") == 2;
		map->remove("t");
		passed = passed && map->size() == 2 &&
			map->countEven("t") == 1 && map->countEven("tttt") == 1;
		map->remove("ttt");
		map->remove("ttt");
		passed = passed && map->size() == 1 &&
			map->countEven("t") == 1 && map->countEven("tttt") == 1;
		map->remove("ttttttb");
		passed = passed && map->size() == 0 &&
			map->countEven("t") == 0 && map->countEven("tttt") == 0;

		break;
	case 10:
		map->add("ttttttttt", 6);
		map->add("t", 2);
		map->add("tttt", 3);
		map->add("t", 1);
		map->add("tt", 10);
		map->add("tttb", 12);
		passed = map->size() == 5 && map->countEven("t") == 3 &&
			map->countEven("tt") == 3 && map->countEven("tttt") == 1;
		map->remove("ttttttttt");
		passed = passed && map->size() == 4 &&
			map->countEven("t") == 2 && map->countEven("tttt") == 0;
		map->remove("tttt");
		map->remove("tt");
		passed = passed && map->size() == 2 &&
			map->countEven("t") == 1 && map->countEven("tttb") == 1;
		map->remove("t");
		map->remove("t");
		passed = passed && map->size() == 1 &&
			map->countEven("t") == 1 && map->countEven("tttb") == 1;
		map->remove("tttb");
		passed = passed && map->size() == 0 &&
			map->countEven("t") == 0;

		break;
	case 11:
		passed = map->size() == 0 && map->countEven("t") == 0;
		map->remove("t");
		map->add("ttttttttt", 6);
		map->add("t", 2);
		passed = passed && map->size() == 2 && map->countEven("t") == 2;
		map->add("ttttttttt", 1);
		map->remove("ttttttttt");
		passed = passed && map->size() == 1 &&
			map->countEven("t") == 1 && map->countEven("tttt") == 0;
		break;
	case 12:
		map->remove("tlt");
		map->remove("tlt");
		map->add("tlt", 6);
		map->add("tlt", 6);
		map->add("tbbt", 1);
		map->add("tbbt", 1);
		map->add("tbbt", 1);
		map->remove("tbbt");
		map->remove("tbbt");
		passed = map->size() == 1 && map->countEven("t") == 1 &&
			map->countEven("tlt") == 1;
		break;
	case 13:
		map->add("tt", 4);
		map->add("tttt", 2);
		map->remove("tt");
		map->add("tt", 3);

		passed = map->size() == 2 && map->countEven("t") == 1;

		break;
	case 14:
		map->add("t", 11);
		map->add("tt", 85);
		map->add("b", 22);
		map->add("bb", 61);
		map->remove("t");
		map->remove("b");
		map->add("t", 9);
		map->add("b", 81);
		map->add("bb", 86);
		passed = map->size() == 4 && map->countEven("b") == 1;

		break;
	case 15:
		map->add("ttttt", 4);
		map->add("ttt", 8);
		map->remove("ttt");
		map->remove("ttt");
		passed = map->size() == 1 && map->countEven("t") == 1;

		break;
		// random tests
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
		int numKeysToAddRemove = 100;
		int keyMaxSize = 6;
		setRandomSeed(testNum * 10);
		Map<string, int> clone;
		addRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "ab", &clone);
		passed = isCorrect(map, clone);
		removeRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "ab", &clone);
		passed = passed && isCorrect(map, clone);
		addRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "ab", &clone);
		passed = passed && isCorrect(map, clone);
		removeRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "ab", &clone);
		passed = passed && isCorrect(map, clone);

		break;
		// efficiency tests
	};
	if (testNum > 20) {
		int numKeysToAddRemove = 10000;
		int keyMaxSize = 10;
		setRandomSeed(testNum * 10);
		Map<string, int> clone;
		addRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "abc", NULL);
		removeRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "abc", NULL);
		addRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "abc", NULL);
		removeRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "abc", NULL);
		addRandomStrings(map, numKeysToAddRemove, keyMaxSize, "", "abc", NULL);
		for (int i = 0; i < 10; i++) {
			string key = getRandomString(randomInteger(1, keyMaxSize), "abc");
			// search multiple times
			for (int j = 0; j < 10000; j++) {
				map->countEven(key);
			}
			if (map->countEven(key) != MAP_ANSW[testNum - 21][i]) {
				return false;
			}
			//outp << map->countEven(key) << ";";
		}
		//outp << endl;
		return true;
	}

	return passed;
}

void runMapSumTests() {
	cout << "### Run Map tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum <= MAP_SUM_TEST_NUM; testNum++) {
		bool res = runMapSumTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << "/" << MAP_SUM_TEST_NUM << " tests ######" << endl;
}

#define TEST_RESULTS_FOLDER_PATH "D:\\freeuni\\courses\\cs106b\\exams repo\\cs106b\\testing\\"
void runTestFromTesterFile() {
	string testFile = string(TEST_RESULTS_FOLDER_PATH) + "test.txt";
	ifstream inp(testFile.c_str());
	string problemName;
	int testNum;
	inp >> problemName >> testNum;

	string outputFile = string(TEST_RESULTS_FOLDER_PATH) + "result.txt";

	bool passed = runMapSumTest(testNum);
	ofstream out(outputFile.c_str());
	if (passed) {
		out << testNum << endl;
	}
	out.close();
}

int main() {
	runMapSumTests();
	//	runTestFromTesterFile();
	cout << "end" << endl;

	//outp.close();
	return 0;
}
