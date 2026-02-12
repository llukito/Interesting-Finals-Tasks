#ifndef MapCount_Included
#define MapCount_Included

#include "console.h"
#include "error.h"
#include <cstdlib>
#include "unordered_map"

using namespace std;

class MapCount {
public:
	MapCount();
	void add(string key, int val);
	int size();
	int countEven(string prefix);
	void remove(string key);

private:
	struct Node {
		Node* children[26];
		int count;
	};
	unordered_map<string, int> map;
	Node* root;
	int loglen;
	void update(Node*& root, string key, int up);
};

#endif;