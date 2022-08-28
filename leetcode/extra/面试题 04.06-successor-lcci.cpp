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
        auto upd = [&](TreeNode *rt) {
            for( ; rt != nullptr; rt = rt -> left)
                stk.push(rt);
        };
        upd(root);
        while(stk.top() != p) {
            TreeNode *cur = stk.top();
            stk.pop();
            upd(cur -> right);
        }
        stk.pop();
        upd(p -> right);
        return stk.empty() ? nullptr : stk.top();
    }
};
