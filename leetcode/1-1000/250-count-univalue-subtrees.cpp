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
            return INT_MAX;
        int ret = rt -> val, tmp;
        for(TreeNode *tr: {rt -> left, rt -> right})
            if(tr != nullptr) {
                tmp = dfs(tr, ans);
                ret = ret == tmp ? ret : INT_MAX;
            }
        ans += ret != INT_MAX;
        return ret;
    }
public:
    int countUnivalSubtrees(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
