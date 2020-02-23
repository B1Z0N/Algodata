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
    vector<TreeNode*> generateTrees(int end, int start = 1) {
        if (start > end) return {};
        vector<TreeNode*> res;
        for (int i = start; i <= end; ++i) {
            auto rightTree = generateTrees(end, i + 1);
            auto leftTree = generateTrees(i - 1, start);
            if (rightTree.size() == 0) rightTree.push_back(nullptr);
            if (leftTree.size() == 0) leftTree.push_back(nullptr);
            
            for (auto &right : rightTree) {
                for (auto &left : leftTree) {
                    auto *root = new TreeNode{i};
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
        }
        
        return res;
    }
};
