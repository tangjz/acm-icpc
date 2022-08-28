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
    void dfs(TreeNode *rt, int dep, vector<int> &vals) {
        if(rt == nullptr)
            return;
        if(dep == vals.size()) {
            vals.push_back(rt -> val);
        } else {
            vals[dep] = max(vals[dep], rt -> val);
        }
        dfs(rt -> left, dep + 1, vals);
        dfs(rt -> right, dep + 1, vals);
    }
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> vals;
        dfs(root, 0, vals);
        return vals;
    }
};
