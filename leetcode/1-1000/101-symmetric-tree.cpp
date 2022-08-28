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
    bool isSymmetric(TreeNode* lft, TreeNode *rht) {
        if(lft == nullptr || rht == nullptr)
            return lft == rht;
        return lft -> val == rht -> val && isSymmetric(lft -> left, rht -> right) && isSymmetric(lft -> right, rht -> left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return isSymmetric(root -> left, root -> right);
    }
};
