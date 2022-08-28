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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> seq;
        dfs(root1, seq);
        int n = seq.size();
        dfs(root2, seq);
        inplace_merge(seq.begin(), seq.begin() + n, seq.end());
        return move(seq);
    }
};
