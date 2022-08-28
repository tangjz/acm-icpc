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
    void flatten(TreeNode* root) {
        while(root != nullptr) {
            if(root -> left != nullptr) {
                TreeNode *ptr = root -> left;
                for( ; ptr -> right != nullptr; ptr = ptr -> right);
                ptr -> right = root -> right;
                root -> right = root -> left;
                root -> left = nullptr;
            }
            root = root -> right;
        }
    }
};
