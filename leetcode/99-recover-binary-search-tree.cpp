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
    void dfs(TreeNode *rt, int &pos, vector<int> &vals) {
        if(rt == nullptr)
            return;
        dfs(rt -> left, pos, vals);
        if(pos == -1) {
            vals.push_back(rt -> val);
        } else {
            rt -> val = vals[pos++];
        }
        dfs(rt -> right, pos, vals);
    }
public:
    void recoverTree(TreeNode* root) {
        int pos;
        vector<int> vals;
        dfs(root, pos = -1, vals);
        sort(vals.begin(), vals.end());
        dfs(root, pos = 0, vals);
    }
};
