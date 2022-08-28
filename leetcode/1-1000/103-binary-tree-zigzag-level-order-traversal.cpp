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
    void dfs(TreeNode *rt, int dep, vector<vector<int> > &ret) {
        if(rt == NULL)
            return;
        if(dep == ret.size())
            ret.push_back(vector<int>());
        ret[dep].push_back(rt -> val);
        dfs(rt -> left, dep + 1, ret);
        dfs(rt -> right, dep + 1, ret);
    }
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > ret;
        dfs(root, 0, ret);
        for(int i = 1, sz = (int)ret.size(); i < sz; i += 2)
            reverse(ret[i].begin(), ret[i].end());
        return ret;
    }
};
