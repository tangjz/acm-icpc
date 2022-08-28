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
    int dfs(TreeNode *rt, bool &ans) {
        if(rt == nullptr || !ans)
            return 0;
        int lft = dfs(rt -> left, ans);
        int rht = dfs(rt -> right, ans);
        ans &= abs(lft - rht) <= 1;
        return ans ? max(lft, rht) + 1 : 0;
    }
public:
    bool isBalanced(TreeNode* root) {
        bool ans = true;
        dfs(root, ans);
        return ans;
    }
};
