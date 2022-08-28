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
    int minDepth(TreeNode* root) {
        if(root == nullptr)
            return 0;
        int ret = 1;
        for(TreeNode *tr: {root -> left, root -> right}) {
            int tmp = minDepth(tr);
            if(tmp && (ret == 1 || ret > tmp))
                ret = tmp + 1;
        }
        return ret;
    }
};
