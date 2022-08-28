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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        stack<TreeNode *> lft, rht;
        auto ext = [&](stack<TreeNode *> &stk, TreeNode *rt) {
            for( ; rt != nullptr; stk.push(rt), rt = rt -> left);
        };
        ext(lft, root1);
        ext(rht, root2);
        while(!lft.empty() || !rht.empty()) {
            int vL = -1, vR = -1;
            while(!lft.empty()) {
                TreeNode *rt = lft.top();
                lft.pop();
                ext(lft, rt -> right);
                if(rt -> left == nullptr && rt -> right == nullptr) {
                    vL = rt -> val;
                    break;
                }
            }
            while(!rht.empty()) {
                TreeNode *rt = rht.top();
                rht.pop();
                ext(rht, rt -> right);
                if(rt -> left == nullptr && rt -> right == nullptr) {
                    vR = rt -> val;
                    break;
                }
            }
            if(vL != vR)
                return 0;
        }
        return 1;
    }
};
