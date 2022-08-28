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
public:
    TreeNode* bstToGst(TreeNode* root) {
        int sum = 0;
        stack<TreeNode *> stk;
        auto append = [&](TreeNode *rt) {
            while(rt != nullptr) {
                stk.push(rt);
                rt = rt -> right;
            }
        };
        append(root);
        while(!stk.empty()) {
            TreeNode *cur = stk.top();
            stk.pop();
            sum += cur -> val;
            cur -> val = sum;
            append(cur -> left);
        }
        return root;
    }
};
