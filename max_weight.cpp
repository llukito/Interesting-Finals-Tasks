#include "max_weight.h"
#include "Set.h"

bool done(int w, Vector<int>& items, int left, int right, int idx) {
	if (idx == items.size()) {
		return abs(left - right) == w;
	}
	if (done(w, items, left + items[idx], right, idx + 1)) {
		return true;
	}
	if (done(w, items, left, right + items[idx], idx + 1)) {
		return true;
	}
	if (done(w, items, left, right, idx + 1)) {
		return true;
	}
	return false;
}

bool possible(int w1, int w2, Vector<int>& items) {
	if (done(w1, items, 0, 0,0)) {
		items.push_back(w1);
		if (done(w2, items, 0, 0,0)) {
			items.remove(items.size() - 1);
			return true;
		}
		items.remove(items.size() - 1);
	}
	return false;
}

int maxWeight(Vector<int>& weights, Vector<int>& items) {
	int res = 0;
	for (int i = 0; i < items.size(); i++) {
		for (int j = 0; j < items.size(); j++) {
			if (i == j)continue;
			if (possible(items[i], items[j], weights)) {
				res = max(res, items[i] + items[j]);
			}
		}
	}
	return res;
}
