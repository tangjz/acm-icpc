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
        int ret = 1;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            int tmp = dfs(tr, ans);
            if(tr -> val == rt -> val + 1)
                ret = max(ret, tmp + 1);
        }
        ans = max(ans, ret);
        return ret;
    }
public:
    int longestConsecutive(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
