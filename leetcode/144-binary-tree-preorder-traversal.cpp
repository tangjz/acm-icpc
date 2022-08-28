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
    void dfs(TreeNode *root, vector<int> &ret) {
        if(root == NULL)
            return;
        ret.push_back(root -> val);
        dfs(root -> left, ret);
        dfs(root -> right, ret);
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        dfs(root, ret);
        return ret;
    }
};
