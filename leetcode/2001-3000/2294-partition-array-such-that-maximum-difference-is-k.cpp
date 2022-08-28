class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 0;
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && nums[i] - nums[j] <= k; ++i);
            ++ans;
        }
        return ans;
    }
};
