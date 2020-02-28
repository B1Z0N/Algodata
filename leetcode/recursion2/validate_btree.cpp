/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        bool res = true;
        if (root->left) res &= (isLess(root->left, root->val) && isValidBST(root->left));
        if (root->right) res &= (isGreater(root->right, root->val) && isValidBST(root->right));
        
        return res;
    }
    
    bool isGreater(TreeNode* root, int val) {
        if (root == nullptr) return true;
        return root->val > val && isGreater(root->left, val) && isGreater(root->right, val);
    }
    
    bool isLess(TreeNode* root, int val) {
        if (root == nullptr) return true;
        return root->val < val && isLess(root->left, val) && isLess(root->right, val);
    }
};
