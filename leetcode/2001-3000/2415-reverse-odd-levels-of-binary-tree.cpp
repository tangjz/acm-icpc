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
    void dfs(TreeNode *rt, int dep, vector<vector<TreeNode *> > &seq) {
        if(rt == nullptr)
            return;
        if(dep == seq.size())
            seq.push_back({});
        seq[dep].push_back(rt);
        dfs(rt -> left, dep + 1, seq);
        dfs(rt -> right, dep + 1, seq);
    }
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        vector<vector<TreeNode *> > seq;
        dfs(root, 0, seq);
        for(int i = 1; i < (int)seq.size(); i += 2)
            for(int j = 0, k = (int)seq[i].size() - 1; j < k; ++j, --k) {
                TreeNode *p = seq[i][j], *q = seq[i][k];
                swap(p -> val, q -> val);
            }
        return root;
    }
};
