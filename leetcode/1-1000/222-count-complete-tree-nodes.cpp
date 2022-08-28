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
    int toLeft(TreeNode *root) {
        int dep = 0;
        for( ; root != NULL; ++dep, root = root -> left);
        return dep;
    }
public:
    int countNodes(TreeNode* root) {
        int ret = 0;
        for(int i = toLeft(root); i > 0; --i)
            if(toLeft(root -> right) == i - 1) {
                ret += 1 << (i - 1);
                root = root -> right;
            } else {
                ret += 1 << (i - 2);
                root = root -> left;
            }
        return ret;
    }
};
