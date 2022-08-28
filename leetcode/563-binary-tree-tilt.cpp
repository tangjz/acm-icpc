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
    int calc(TreeNode *rt, int &sum) {
        if(rt == nullptr)
            return 0;
        int cL = calc(rt -> left, sum);
        int cR = calc(rt -> right, sum);
        sum += abs(cL - cR);
        return (rt -> val) + cL + cR;
    }
public:
    int findTilt(TreeNode* root) {
        int sum = 0;
        calc(root, sum);
        return sum;
    }
};
