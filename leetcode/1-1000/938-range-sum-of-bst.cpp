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
    int rangeSumBST(TreeNode* rt, int low, int high) {
        if(rt == nullptr)
            return 0;
        int ret = 0;
        if(low <= rt -> val && rt -> val <= high)
            ret += rt -> val;
        if(low < rt -> val)
            ret += rangeSumBST(rt -> left, low, min(rt -> val - 1, high));
        if(rt -> val < high)
            ret += rangeSumBST(rt -> right, max(rt -> val + 1, low), high);
        return ret;
    }
};
