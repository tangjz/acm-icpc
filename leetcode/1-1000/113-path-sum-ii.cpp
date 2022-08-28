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
    void dfs(TreeNode *rt, int rem, vector<int> &path, vector<vector<int> > &ret) {
        if(rt == nullptr)
            return;
        path.push_back(rt -> val);
        rem -= rt -> val;
        if(rt -> left == nullptr && rt -> right == nullptr) {
            if(!rem)
                ret.push_back(path);
        } else {
            dfs(rt -> left, rem, path, ret);
            dfs(rt -> right, rem, path, ret);
        }
        path.pop_back();
        rem += rt -> val;
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int> > ret;
        vector<int> path;
        dfs(root, targetSum, path, ret);
        return ret;
    }
};
