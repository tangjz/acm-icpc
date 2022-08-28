class Solution {
public:
    int longestSubsequence(vector<int>& arr, int diff) {
        int ans = 0;
        unordered_map<int, int> dp;
        for(int x: arr) {
            int best = 0;
            auto it = dp.find(x - diff);
            if(it != dp.end()) {
                best = it -> second;
            }
            ans = max(ans, dp[x] = max(dp[x], best + 1));
        }
        return ans;
    }
};
