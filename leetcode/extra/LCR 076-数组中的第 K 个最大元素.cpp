class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(), nums.end() - k, nums.end());
        return *(nums.end() - k);
    }
};
