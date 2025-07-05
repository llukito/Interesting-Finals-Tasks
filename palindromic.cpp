#include "Palindromic.h"
#include "unordered_map"

void check(TreeNode* root, int& res, unordered_map<int, int>& map) {
	if (!root)return;
	if (!root->left && !root->right) {
		map[root->v]++;
		int odd = 1;
		for (auto& entry : map) {
			if (entry.second % 2 == 1) {
				odd--;
				if (odd < 0) {
					map[root->v]--;
					return;
				}
			}
		}
		map[root->v]--;
		res++;
		return;
	}
	map[root->v]++;
	check(root->left, res, map);
	check(root->right, res, map);
	map[root->v]--;
}

int pseudoPalindromicPaths(TreeNode* root) {
	int res = 0;
	unordered_map<int, int> map;
	check(root, res, map);
	return res;
}