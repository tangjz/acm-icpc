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
    pair<int, int> dfs(TreeNode *rt, int val, int &ans) {
        if(rt == nullptr)
            return {-1, -1};
        pair<int, int> ret = {0, -1};
        if(val == rt -> val)
            ret.second = 0;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            pair<int, int> tmp = dfs(tr, val, ans);
            if(ret.second != -1) {
                ans = max(ans, ret.second + tmp.first + 1);
            } else if(tmp.second != -1) {
                ans = max(ans, ret.first + tmp.second + 1);
                ret.second = tmp.second + 1;
            }
            ret.first = max(ret.first, tmp.first + 1);
        }
        return ret;
    }
public:
    int amountOfTime(TreeNode* root, int start) {
        int ans = 0;
        dfs(root, start, ans);
        return ans;
    }
};
