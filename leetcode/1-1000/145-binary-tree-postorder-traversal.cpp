/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    void dfs(TreeNode *root, vector<int> &ret) {
        if(root == NULL)
            return;
        dfs(root -> left, ret);
        dfs(root -> right, ret);
        ret.push_back(root -> val);
    }
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ret;
        dfs(root, ret);
        return ret;
    }
};
