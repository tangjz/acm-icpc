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
    typedef long long LL;
    void dfs(TreeNode *rt, int dep, vector<pair<int, LL> > &seq) {
        if(rt == nullptr)
            return;
        if(dep == seq.size())
            seq.push_back({});
        ++seq[dep].first;
        seq[dep].second += rt -> val;
        dfs(rt -> left, dep + 1, seq);
        dfs(rt -> right, dep + 1, seq);
    }
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<pair<int, LL> > seq;
        dfs(root, 0, seq);
        vector<double> ans;
        for(auto &it: seq)
            ans.push_back((double)it.second / it.first);
        return ans;
    }
};
