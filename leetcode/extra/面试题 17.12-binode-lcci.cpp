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
    void dfs(TreeNode *rt, TreeNode* &nxt) {
        if(rt == nullptr)
            return;
        dfs(rt -> right, nxt);
        rt -> right = nxt;
        nxt = rt;
        dfs(rt -> left, nxt);
        rt -> left = nullptr;
    }
public:
    TreeNode* convertBiNode(TreeNode* root) {
        TreeNode *nxt = nullptr;
        dfs(root, nxt);
        return nxt;
    }
};
