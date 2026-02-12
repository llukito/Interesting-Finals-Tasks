
#include "mapcount.h"

MapCount::MapCount() {
	loglen = 0;
	root = new Node();
	root->count = 0;
	for (int i = 0; i < 26; i++) {
		root->children[i] = nullptr;
	}
}

void MapCount::update(Node*& root,string key, int up) {
	if (!root) {
		root = new Node();
		root->count = 0;
		for (int i = 0; i < 26; i++) {
			root->children[i] = nullptr;
		}
	}
	root->count += up;
	if (key.empty())return;
	update(root->children[key[0] - 'a'], key.substr(1), up);
}

void MapCount::add(string key, int val) {
	if (map.count(key)) {
		remove(key);
		map[key] = val;
		if (val % 2 == 0) {
			update(root,key, 1);
		}
		loglen++;
	}
	else {
		map[key] = val;
		if (val % 2 == 0) {
			update(root, key, 1);
		}
		loglen++;
	}
}

int MapCount::size() {
	return loglen;
}

int MapCount::countEven(string prefix) {
	Node* head = root;
	int idx = 0;
	while (prefix.size() != idx) {
		if (!head)return 0;
		head = head->children[prefix[idx++] - 'a'];
	}
	return head ? head->count : 0;
}

void MapCount::remove(string key) {
	if (map.count(key)) {
		int val = map[key];
		map.erase(key);
		loglen--;
		if (val % 2 == 0) {
			update(root, key, -1);
		}
	}
}
