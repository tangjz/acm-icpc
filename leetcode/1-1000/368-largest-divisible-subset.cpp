class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        pair<int, int> ans;
        vector<pair<int, int> > dp(n);
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i) {
            dp[i] = {1, -1};
            for(int j = 0; j < i; ++j)
                if(nums[i] % nums[j] == 0)
                    dp[i] = max(dp[i], make_pair(dp[j].first + 1, j));
            ans = max(ans, {dp[i].first, i});
        }
        vector<int> ret;
        for(int x = ans.second; x != -1; x = dp[x].second)
            ret.push_back(nums[x]);
        return ret;
    }
};
