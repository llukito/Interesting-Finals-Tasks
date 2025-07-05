
#include "SumOfLeftLeaves.h"

void check(TreeNode* root, int& res, bool left) {
	if (!root)return;
	if (!root->left && !root->right) {
		if (left) {
			res += root->v;
		}
		return;
	}
	check(root->left, res, true);
	check(root->right, res, false);
}

int sumOfLeftLeaves(TreeNode* root) {
	int res = 0;
	check(root, res, false);
	return res;
}

