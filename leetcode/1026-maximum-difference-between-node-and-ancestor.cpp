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
        pair<int, int> ret = {INT_MAX, INT_MIN}, tmp;
        if(rt != nullptr) {
            tmp = dfs(rt -> left, ans);
            ret = {min(ret.first, tmp.first), max(ret.second, tmp.second)};
            tmp = dfs(rt -> right, ans);
            ret = {min(ret.first, tmp.first), max(ret.second, tmp.second)};
            ret = {min(ret.first, rt -> val), max(ret.second, rt -> val)};
            ans = max(ans, max(rt -> val - ret.first, ret.second - rt -> val));
        }
        return ret;
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
