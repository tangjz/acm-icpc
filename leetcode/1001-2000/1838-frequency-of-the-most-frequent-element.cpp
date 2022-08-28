class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = (int)nums.size();
        sort(nums.begin(), nums.end());
        int ans = 1;
        long long sum = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < i && sum > k; ++j)
                sum -= nums[i] - nums[j];
            ans = max(ans, i - j + 1);
            if(i + 1 < n)
                sum += (i - j + 1LL) * (nums[i + 1] - nums[i]);
        }
        return ans;
    }
};
