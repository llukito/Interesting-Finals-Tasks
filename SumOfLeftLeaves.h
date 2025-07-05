#ifndef SumOfLeftLeaves_Included
#define SumOfLeftLeaves_Included

#include "console.h"
#include "error.h"

using namespace std;

struct TreeNode {
	int v;
	TreeNode* left;
	TreeNode* right;

	int weight;//ignore this field
};

int sumOfLeftLeaves(TreeNode* root);


#endif;