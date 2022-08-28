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
    void dfs(TreeNode *rt, int &sum) {
        if(rt == nullptr)
            return;
        dfs(rt -> right, sum);
        rt -> val = (sum += rt -> val);
        dfs(rt -> left, sum);
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        dfs(root, sum);
        return root;
    }
};
