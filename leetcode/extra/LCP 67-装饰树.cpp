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
    TreeNode* expandBinaryTree(TreeNode* root) {
        if(root != nullptr) {
            if(root -> left != nullptr) {
                root -> left = new TreeNode(-1, expandBinaryTree(root -> left), nullptr);
            }
            if(root -> right != nullptr) {
                root -> right = new TreeNode(-1, nullptr, expandBinaryTree(root -> right));
            }
        }
        return root;
    }
};
