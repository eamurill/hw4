#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool checkEqualPaths(Node* root, int depth, int& leafDepth);

bool checkEqualPaths(Node* root, int depth, int& leafDepth){
	if (!root) return true; // Base case: Null nodes are valid

    // If it's a leaf node, check its depth
    if (!root->left && !root->right) {
        if (leafDepth == -1) { 
            leafDepth = depth; // Store the first leaf's depth
            return true;
        }
        return depth == leafDepth; // Ensure all leaves match the first one's depth
    }

    // Recursively check both left and right subtrees
    return checkEqualPaths(root->left, depth + 1, leafDepth) &&
           checkEqualPaths(root->right, depth + 1, leafDepth);
}


bool equalPaths(Node * root)
{
    // Add your code below
		int leafDepth = -1; // To store the first leaf's depth
    return checkEqualPaths(root, 0, leafDepth);
}

