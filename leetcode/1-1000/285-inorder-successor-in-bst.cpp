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
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode *> stk;
        auto extend = [&](TreeNode *rt) {
            for( ; rt != nullptr; rt = rt -> left)
                stk.push(rt);
        };
        extend(root);
        TreeNode *las = nullptr;
        do {
            las = stk.top();
            stk.pop();
            extend(las -> right);
        } while(las != p);
        return stk.empty() ? nullptr : stk.top();
    }
};
