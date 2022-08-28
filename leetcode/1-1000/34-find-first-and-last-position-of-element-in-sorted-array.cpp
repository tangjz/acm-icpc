class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto it = lower_bound(nums.begin(), nums.end(), target);
        if(it == nums.end() || *it != target)
            return {-1, -1};
        auto jt = upper_bound(nums.begin(), nums.end(), target);
        return {(int)(it - nums.begin()), (int)(jt - nums.begin() - 1)};
    }
};
