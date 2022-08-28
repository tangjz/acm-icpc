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
    void dfs(TreeNode *rt, int dep, vector<int> &ret) {
        if(rt == nullptr)
            return;
        if(dep == ret.size()) {
            ret.push_back(rt -> val);
        } else {
            ret[dep] = rt -> val;
        }
        dfs(rt -> left, dep + 1, ret);
        dfs(rt -> right, dep + 1, ret);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ret;
        dfs(root, 0, ret);
        return ret;
    }
};
