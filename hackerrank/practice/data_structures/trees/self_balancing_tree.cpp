#include <bits/stdc++.h>

/* Node is defined as  :
typedef struct node {
	int val;
	struct node *left;
	struct node *right;
	int ht;
} node;
*/

void right_rotate(node *&root) {
	node* new_root = root->left;
	root->left = root->left->right;
        new_root->right = root;
	root = new_root;	
}

void left_rotate(node *&root) {
	node* new_root = root->right;
	root->right = root->right->left;
        new_root->left = root;
	root = new_root;	
}

inline int height(node *nd) { return nd ? nd->ht : -1; }

bool balanced(node *root) {
	return abs(height(root->left) - height(root->right)) < 2;
}

void balance(node *&gparent, int child_val) {
	if (balanced(gparent)) return;

	if (gparent->left->right->val == child_val) {
		child_val = gparent->left->val;
		left_rotate(gparent->left);
	} else if (gparent->right->left->val == child_val) {
		child_val = gparent->right->val;
		right_rotate(gparent->right);
	}

	if (gparent->left->left->val == child_val) {
		right_rotate(gparent);	
	} else if (gparent->right->right->val == child_val) {
		left_rotate(gparent);
	}
}

node *insert(node *root, int val) {
    if (root == nullptr) return new node{val};

    if (root->val > val) {
        root->left = insert(root->left, val);
    } else if (root->val < val) {
        root->right = insert(root->right, val);
    } else {}
    
    balance(root, val);
    return root;
}
