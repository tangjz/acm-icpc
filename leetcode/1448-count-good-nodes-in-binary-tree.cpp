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
    int dfs(TreeNode *root, int upp = INT_MIN) {
        if(root == NULL)
            return 0;
        int ret = root -> val >= upp;
        upp = max(upp, root -> val);
        ret += dfs(root -> left, upp);
        ret += dfs(root -> right, upp);
        return ret;
    }
public:
    int goodNodes(TreeNode* root) {
        return dfs(root);
    }
};
