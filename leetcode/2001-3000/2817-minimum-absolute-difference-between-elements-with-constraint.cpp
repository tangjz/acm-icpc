class Solution {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
        int n = nums.size(), ans = INT_MAX;
        set<int> sp;
        for(int i = x; i < n; ++i) {
            sp.insert(nums[i - x]);
            auto it = sp.lower_bound(nums[i]);
            if(it != sp.end())
                ans = min(ans, *it - nums[i]);
            if(it != sp.begin())
                ans = min(ans, nums[i] - *(--it));
        }
        return ans;
    }
};
