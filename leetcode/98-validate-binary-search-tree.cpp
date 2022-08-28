/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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
        return dfs(root, INT_MIN, INT_MAX);
    }
};
