class Solution {
public:
    int smallestRangeI(vector<int>& nums, int k) {
        int dt = *max_element(nums.begin(), nums.end()) - *min_element(nums.begin(), nums.end());
        return max(dt - k - k, 0);
    }
};
