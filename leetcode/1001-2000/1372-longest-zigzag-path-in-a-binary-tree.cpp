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
    pair<int, int> dfs(TreeNode *rt, int &ans) {
        pair<int, int> ret = {0, 0};
        if(rt != NULL) {
            if(rt -> left != NULL)
                ret.first = dfs(rt -> left, ans).second + 1;
            if(rt -> right != NULL)
                ret.second = dfs(rt -> right, ans).first + 1;
            ans = max(ans, max(ret.first, ret.second));
        }
        return ret;
    }
public:
    int longestZigZag(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
