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
    void dfs(TreeNode *rt, vector<int> &seq) {
        if(rt == nullptr)
            return;
        dfs(rt -> left, seq);
        seq.push_back(rt -> val);
        dfs(rt -> right, seq);
    }
public:
    vector<vector<int>> closestNodes(TreeNode* rt, vector<int>& que) {
        vector<int> seq;
        dfs(rt, seq);
        vector<vector<int> > ret;
        for(int x: que) {
            auto it = lower_bound(seq.begin(), seq.end(), x);
            int v = it == seq.end() ? -1 : *it;
            int u = v == x ? x : (it == seq.begin() ? -1 : *(--it));
            ret.push_back({u, v});
        }
        return ret;
    }
};
