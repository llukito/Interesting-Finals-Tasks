#include <iostream>
#include <string>
#include "simpio.h"
#include "vector.h"
#include "console.h"
#include <time.h>
#include "operations.h"
#include "random.h"
#include "remove.h"
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

const int RemoveTestsNum = 15;


const int OperationsTestsNum = 20;
int x_y_values[20][2] = { {1, 2}, {1, 1}, {1, 5}, {26, 1}, {54, 2}, {25, 30}, {53, 3}, 
						{61, 3}, {125, 1}, {89, 1}, {31, 12}, {39, 25}, {49, 20}, {17, 7}, 
						{90, 7}, {1000, 16}, {10000, 9}, {5001, 7}, {1000, 970}, {2, 30} };
int operations_answers[20] = {1, 0, 4, 3, 4, 5, 5, 6, 3, 6, 8, 14, 12, 7, 4, 6, 9, 6, 30, 28 };


bool runOperationsSingleTest(int testNum) {
	int res = minOper(x_y_values[testNum - 1][0], x_y_values[testNum - 1][1]);
	bool passed = res == operations_answers[testNum - 1];
	if (!passed) {
		cout << res << " " << operations_answers[testNum - 1] << endl;
	}
	return passed;
}

ListNode* vectorToList(Vector<int>& v) {
	ListNode* head = NULL;
	for (int i = v.size() - 1; i >= 0; i--) {
		ListNode* tmp = new ListNode;
		tmp->val = v[i];
		tmp->next = head;
		head = tmp;
	}
	return head;
}

bool isCorrect(ListNode* list, Vector<int>& nums) {
	for (int i = 0; i < nums.size(); i++) {
		if (list == NULL || list->val != nums[i]) return false;
		list = list->next;
	}
	return list == NULL;
}

int answers[5] = { 14, 13, 12, 12, 15 };
bool runRemoveSingleTest(int testNum) {
	Vector<int> nums;
	Vector<int> res;
	ListNode* list;
	bool passed = false;
	switch (testNum) {
	case 1:
		nums += 1, 7, 3, 9;
		res += 9;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 2:
		nums += 5, 2, 13, 3, 8;
		res += 13, 8;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 3:
		nums += 1, 1, 1, 1;
		res += 1, 1, 1, 1;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 4:
		nums += 2, 3, 6, 14, 7, 1, 16, 14, 17, 13, 8;
		res += 17, 13, 8;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 5:
		nums += 100, 11, 12, 9, 12, 15, 18, 9, 7;
		res += 100, 18, 9, 7;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 6:
		nums += 1, 7, 3, 9, 5, 7, 17, 13, 2, 5, 7, 5, 1, 3;
		res += 17, 13, 7, 5, 3;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 7:
		nums += 14, 5, 17, 11, 3, 7, 2, 9, 19, 8, 8, 12, 10, 11, 7, 8;
		res += 19, 12, 11, 8;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 8:
		nums += 9, 14, 20, 15, 19, 3, 7, 16, 13, 3, 13, 7, 19, 19, 1, 7, 3, 9;
		res += 20, 19, 19, 19, 9;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 9:
		nums += 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1;
		res += 10, 9, 8, 7, 6, 5, 4, 3, 2, 1;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 10:
		nums += 12, 10, 4, 1, 10, 20, 3, 11, 19, 2, 1, 3, 9, 14, 10, 18, 11, 18, 6, 9, 18, 16, 8, 3, 13, 3, 1, 4, 14, 15;
		res += 20, 19, 18, 18, 18, 16, 15;
		list = vectorToList(nums);
		list = removeNodes(list);
		passed = isCorrect(list, res);
		break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		setRandomSeed(testNum);
		for (int i = 0; i < 100000; i++) {
			nums += randomInteger(0, 150000);
		}
		
		list = vectorToList(nums);
		list = removeNodes(list);
		int size = 0;
		while (list != NULL) {
			size++;
			list = list->next;
		}
		passed = size == answers[testNum-11];
		break;
	}
	return passed;
}

void runOperationsAllTests() {
	cout << "### Run Opeerations tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum <= OperationsTestsNum; testNum++) {
		bool passed = runOperationsSingleTest(testNum);
		printTestResults(passed, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

void runRemoveAllTests() {
	cout << "### Run Remove tests ###" << endl;
	int passedNum = 0;
	int testNum = 1;

	for (; testNum <= RemoveTestsNum; testNum++) {
		bool passed = runRemoveSingleTest(testNum);
		printTestResults(passed, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	//runOperationsAllTests();
	runRemoveAllTests();
	cout << "end" << endl;
	return 0;
}
