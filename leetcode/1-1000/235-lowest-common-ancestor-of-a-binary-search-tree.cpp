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
    int dfs(TreeNode *rt, TreeNode *p, TreeNode *q, TreeNode *&ans) {
        if(rt == nullptr)
            return 0;
        int msk = (rt == p) << 1 | (rt == q);
        msk |= dfs(rt -> left, p, q, ans);
        msk |= dfs(rt -> right, p, q, ans);
        if(msk == 3 && ans == nullptr)
            ans = rt;
        return msk;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode *ans = nullptr;
        dfs(root, p, q, ans);
        return ans;
    }
};
