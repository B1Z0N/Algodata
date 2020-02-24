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
    bool isSameTree(TreeNode* fst, TreeNode* snd) {
        queue<TreeNode*> q1, q2;
        q1.push(fst);
        q2.push(snd);
        while (!q1.empty() && !q2.empty()) {
            auto* nd1 = q1.front(); q1.pop();
            auto* nd2 = q2.front(); q2.pop();
            
            if (nd1 == nullptr)
                if (nd2 != nullptr) return false;
                else continue;
            else if (nd2 == nullptr) return false;

            if (nd1->val != nd2->val) return false;
            
            q1.push(nd1->left); q1.push(nd1->right);
            q2.push(nd2->left); q2.push(nd2->right);
        }
        
        if (!q1.empty() || !q2.empty()) return false;
        return true;
    }
};
