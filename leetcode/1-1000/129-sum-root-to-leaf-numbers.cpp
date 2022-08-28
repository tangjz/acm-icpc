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
    int dfs(TreeNode *rt, int pre) {
        pre = pre * 10 + (rt -> val);
        bool lch = rt -> left != NULL;
        bool rch = rt -> right != NULL;
        if(!lch && !rch)
            return pre;
        return (lch ? dfs(rt -> left, pre) : 0) + (rch ? dfs(rt -> right, pre) : 0);
    }
public:
    int sumNumbers(TreeNode* root) {
        return root == NULL ? 0 : dfs(root, 0);
    }
};
