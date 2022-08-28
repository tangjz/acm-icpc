class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int n = nums.size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                for(int k = j + 1; k < n; ++k)
                    ans += nums[j] - nums[i] == diff && nums[k] - nums[j] == diff;
        return ans;
    }
};
