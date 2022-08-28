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
    TreeNode* increasingBST(TreeNode* root, TreeNode *end = nullptr) {
        if(root != nullptr) {
            if(root -> left != nullptr) {
                TreeNode *ptr = increasingBST(root -> left, root);
                root -> left = nullptr;
                root = ptr;
            }
            root -> right = increasingBST(root -> right, end);
        } else {
            root = end;
        }
        return root;
    }
};
