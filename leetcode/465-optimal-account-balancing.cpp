class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> ctr;
        for(auto &it: transactions) {
            ctr[it[0]] -= it[2];
            ctr[it[1]] += it[2];
        }
        vector<int> vec;
        for(auto &it: ctr)
            if(it.second != 0)
                vec.push_back(it.second);
        int n = vec.size(), m = 1 << n;
        vector<int> dp(m);
        dp[0] = 0;
        for(int i = 1; i < m; ++i) {
            int sum = 0;
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1) {
                    sum += vec[j];
                    dp[i] = max(dp[i], dp[i ^ (1 << j)]);
                }
            dp[i] += !sum;
        }
        return n - dp.back();
    }
};
