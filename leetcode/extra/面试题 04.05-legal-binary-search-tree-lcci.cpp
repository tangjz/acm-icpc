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
    bool dfs(TreeNode *rt, int low, int upp) {
        if(rt -> val < low || rt -> val > upp)
            return false;
        if(rt -> left != nullptr) {
            if(rt -> val == low || !dfs(rt -> left, low, rt -> val - 1))
                return false;
        }
        if(rt -> right != nullptr) {
            if(rt -> val == upp || !dfs(rt -> right, rt -> val + 1, upp))
                return false;
        }
        return true;
    }
public:
    bool isValidBST(TreeNode* root) {
        if(root == nullptr)
            return 1;
        return dfs(root, INT_MIN, INT_MAX);
    }
};
