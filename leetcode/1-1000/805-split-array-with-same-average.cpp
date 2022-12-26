class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        const int maxv = (int)3e5 + 1;
        int n = nums.size(), sum = 0;
        vector<bitset<maxv> > dp(n + 1);
        dp[0].set(0);
        for(int x: nums) {
            for(int i = n; i > 0; --i)
                dp[i] |= dp[i - 1] << x;
            sum += x;
        }
        for(int i = 1; i < n; ++i) {
            int val = sum * i;
            if(val % n > 0)
                continue;
            val /= n;
            if(dp[i].test(val))
                return 1;
        }
        return 0;

    }
};
