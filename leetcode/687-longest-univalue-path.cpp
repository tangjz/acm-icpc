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
            return -1;
        int ret = 0;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            int tmp = dfs(tr, ans);
            if(tmp == -1)
                continue;
            if(tr -> val == rt -> val) {
                ++tmp;
                ans = max(ans, ret + tmp);
                ret = max(ret, tmp);
            }
        }
        return ret;
    }
public:
    int longestUnivaluePath(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
