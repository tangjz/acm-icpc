class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto it = lower_bound(nums.begin(), nums.end(), target);
        if(it == nums.end() || *it != target)
            return 0;
        auto jt = upper_bound(it, nums.end(), target);
        return jt - it;
    }
};
