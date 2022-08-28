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
    int dfs(TreeNode *rt, int &ans) {
        if(rt == nullptr)
            return 0;
        static const int maxv = (int)1e5 + 1;
        int ret = min(dfs(rt -> left, ans) + dfs(rt -> right, ans), maxv);
        ans += ret == rt -> val;
        return ret + rt -> val;
    }
public:
    int equalToDescendants(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
