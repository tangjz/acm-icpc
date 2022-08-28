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
        if(rt == NULL)
            return 0;
        int lft = max(dfs(rt -> left, ans), 0);
        int rht = max(dfs(rt -> right, ans), 0);
        ans = max(ans, (rt -> val) + lft + rht);
        return (rt -> val) + max(lft, rht);
    }
public:
    int maxPathSum(TreeNode* root) {
        int ans = root -> val;
        dfs(root, ans);
        return ans;
    }
};
