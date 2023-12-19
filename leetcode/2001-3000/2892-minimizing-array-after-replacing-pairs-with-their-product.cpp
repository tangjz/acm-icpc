class Solution {
public:
    int minArrayLength(vector<int>& nums, int k) {
        if(!*min_element(nums.begin(), nums.end()))
            return 1;
        typedef long long LL;
        int n = nums.size(), L = 0;
        vector<int> dp(n + 1, INT_MAX), que;
        dp[0] = 0;
        que.push_back(0);
        LL prd = 1;
        for(int i = 0, j = 0; i < n; ++i) {
            for(prd *= nums[i]; prd > k; prd /= nums[j++]);
            if(i < j) {
                dp[i + 1] = dp[i] + 1;
            } else {
                for( ; L < que.size() && que[L] < j; ++L);
                dp[i + 1] = dp[que[L]] + 1;
            }
            for( ; L < que.size() && dp[que.back()] >= dp[i + 1]; que.pop_back());
            que.push_back(i + 1);
        }
        return dp[n];
    }
};
