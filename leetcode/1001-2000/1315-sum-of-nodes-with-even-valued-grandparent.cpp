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
    int dfs(TreeNode *rt, int v0 = 1, int v1 = 1) {
        if(rt == NULL)
            return 0;
        int ret = 0;
        if(!(v1 & 1))
            ret += rt -> val;
        v1 = v0;
        v0 = rt -> val;
        ret += dfs(rt -> left, v0, v1);
        ret += dfs(rt -> right, v0, v1);
        return ret;
    }
public:
    int sumEvenGrandparent(TreeNode* root) {
        return dfs(root);
    }
};
