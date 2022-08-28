class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& seq) {
        int m = seq.size();
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        int tot = 1 << m;
        vector<int> sz(tot);
        for(int i = 1; i < tot; ++i) {
            int lbt = i & -i;
            sz[i] = sz[i ^ lbt] + seq[__builtin_ctz(lbt)];
        }
        vector<bool> dp(tot);
        dp[0] = 1;
        for(auto &it: ctr) {
            for(int i = tot - 1; i > 0; --i)
                for(int j = i; j && !dp[i]; j = (j - 1) & i)
                    dp[i] = sz[j] <= it.second && dp[i ^ j];
        }
        return dp.back();
    }
};
