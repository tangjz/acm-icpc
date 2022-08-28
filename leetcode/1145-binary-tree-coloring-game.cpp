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
    int dfs(TreeNode *rt, int n, int x, int &sz) {
        if(rt == nullptr)
            return 0;
        int lft = dfs(rt -> left, n, x, sz);
        int rht = dfs(rt -> right, n, x, sz);
        if(rt -> val == x) {
            sz = max(n - 1 - lft - rht, max(lft, rht));
        }
        return lft + rht + 1;
    }
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        int sz = 0;
        dfs(root, n, x, sz);
        return sz > n - sz;
    }
};
