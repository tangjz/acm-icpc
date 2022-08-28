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
    TreeNode *build(int sta, int len, vector<int> &nums) {
        if(len <= 0)
            return nullptr;
        int half = len >> 1;
        return new TreeNode(nums[sta + half], build(sta, half, nums), build(sta + half + 1, len - half - 1, nums));
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(0, nums.size(), nums);
    }
};
