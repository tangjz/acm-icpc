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
    pair<int, int> dfs(TreeNode *rt, double &ans) {
        if(rt == nullptr)
            return {0, 0};
        pair<int, int> ret = {rt -> val, 1}, tmp;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            tmp = dfs(tr, ans);
            ret.first += tmp.first;
            ret.second += tmp.second;
        }
        ans = max(ans, (double)ret.first / ret.second);
        return ret;
    }
public:
    double maximumAverageSubtree(TreeNode* root) {
        double ans = 0;
        dfs(root, ans);
        return ans;
    }
};
