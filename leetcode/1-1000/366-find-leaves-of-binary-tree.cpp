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
    int dfs(TreeNode *rt, vector<vector<int> > &ret) {
        if(rt == nullptr)
            return -1;
        int lev = max(dfs(rt -> left, ret), dfs(rt -> right, ret)) + 1;
        if(lev == ret.size())
            ret.push_back({});
        ret[lev].push_back(rt -> val);
        return lev;
    }
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int> > ret;
        dfs(root, ret);
        return ret;
    }
};
