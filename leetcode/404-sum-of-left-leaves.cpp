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
    bool isLeaf(TreeNode *rt) {
        return rt != nullptr && rt -> left == nullptr && rt -> right == nullptr;
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        int ret = 0;
        if(root != nullptr && !isLeaf(root)) {
            if(isLeaf(root -> left)) {
                ret += root -> left -> val;
            } else {
                ret += sumOfLeftLeaves(root -> left);
            }
            ret += sumOfLeftLeaves(root -> right);
        }
        return ret;
    }
};
