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
    TreeNode *dfs(vector<int> &nums, int L, int R) {
        if(L > R)
            return nullptr;
        int M = (L + R) / 2;
        TreeNode *rt = new TreeNode(nums[M]);
        rt -> left = dfs(nums, L, M - 1);
        rt -> right = dfs(nums, M + 1, R);
        return rt;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return dfs(nums, 0, nums.size() - 1);
    }
};
