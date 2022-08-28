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
        if(rt == nullptr)
            return {};
        pair<int, int> ret = {1, 1}, tmp;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            tmp = dfs(tr, ans);
            if(tr -> val == rt -> val - 1)
                ret.first = max(ret.first, tmp.first + 1);
            if(tr -> val == rt -> val + 1)
                ret.second = max(ret.second, tmp.second + 1);
        }
        ans = max(ans, ret.first + ret.second - 1);
        return ret;
    }
public:
    int longestConsecutive(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
