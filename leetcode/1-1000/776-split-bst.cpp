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
    vector<TreeNode*> splitBST(TreeNode* root, int target) {
        vector<TreeNode *> ret = {nullptr, nullptr};
        if(root == nullptr)
            return ret;
        if(root -> val <= target) {
            ret = splitBST(root -> right, target);
            root -> right = ret[0];
            ret[0] = root;
        } else {
            ret = splitBST(root -> left, target);
            root -> left = ret[1];
            ret[1] = root;
        }
        return ret;
    }
};
