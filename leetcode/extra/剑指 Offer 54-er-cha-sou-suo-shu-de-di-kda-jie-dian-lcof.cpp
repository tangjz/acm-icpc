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
    int kthLargest(TreeNode* root, int k) {
        stack<TreeNode *> stk;
        auto upd = [&](TreeNode *rt) {
            for( ; rt != nullptr; rt = rt -> right)
                stk.push(rt);
        };
        upd(root);
        for(int i = 1; i < k; ++i) {
            TreeNode *cur = stk.top();
            stk.pop();
            upd(cur -> left);
        }
        return stk.top() -> val;
    }
};
