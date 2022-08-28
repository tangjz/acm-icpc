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
    bool isSymmetric(TreeNode* lft, TreeNode *rht) {
        if(lft == nullptr || rht == nullptr)
            return lft == rht;
        return lft -> val == rht -> val && isSymmetric(lft -> left, rht -> right) && isSymmetric(lft -> right, rht -> left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return root == nullptr || isSymmetric(root -> left, root -> right);
    }
};
