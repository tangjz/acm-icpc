class Solution {
public:
    vector<int> largestSubarray(vector<int>& nums, int k) {
        int pos = max_element(nums.begin(), nums.end() - k + 1) - nums.begin();
        return vector<int>(nums.begin() + pos, nums.begin() + pos + k);
    }
};
