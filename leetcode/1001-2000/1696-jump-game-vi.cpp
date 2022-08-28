class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        // dp[i] = max(dp[j]) + num[i] (i - k <= j < i)
        int n = (int)nums.size();
        vector<int> dp(n);
        deque<int> que;
        for(int i = 0; i < n; ++i) {
            if(i > 0) {
                while(!que.empty() && i - que.front() > k)
                    que.pop_front();
                assert(!que.empty());
                dp[i] = dp[que.front()];
            }
            dp[i] += nums[i];
            while(!que.empty() && dp[que.back()] <= dp[i])
                que.pop_back();
            que.push_back(i);
        }
        return dp.back();
    }
};
