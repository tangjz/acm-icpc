class Solution {
public:
    int countPairs(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                ans += nums[i] == nums[j] && i * j % k == 0;
        return ans;
    }
};
