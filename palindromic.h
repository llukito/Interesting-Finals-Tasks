#ifndef Palindromic_Included
#define Palindromic_Included

#include "console.h"
using namespace std;

struct TreeNode {
	int v;//node value
	int weight;//ignore this field
	TreeNode* left;
	TreeNode* right;
};

int pseudoPalindromicPaths(TreeNode* root);

#endif;