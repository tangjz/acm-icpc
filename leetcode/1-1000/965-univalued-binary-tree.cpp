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
    bool dfs(TreeNode *rt, int val) {
        if(rt == nullptr)
            return 1;
        if(rt -> val != val)
            return 0;
        return dfs(rt -> left, val) && dfs(rt -> right, val);
    }
public:
    bool isUnivalTree(TreeNode* root) {
        return dfs(root, root -> val);
    }
};
