class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int ans = -(int)1e9, len = (int)nums.size();
        vector<int> dp(len + 1, 0);
        deque<int> cand;
        for(int i = 1; i <= len; ++i) {
            dp[i] = 0;
            while(!cand.empty() && i - cand.front() > k)
                cand.pop_front();
            if(!cand.empty())
                dp[i] = max(dp[i], dp[cand.front()]);
            ans = max(ans, dp[i] += nums[i - 1]);
            while(!cand.empty() && dp[i] >= dp[cand.back()])
                cand.pop_back();
            cand.push_back(i);
        }
        return ans;
    }
};
