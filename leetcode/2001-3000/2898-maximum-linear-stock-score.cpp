class Solution {
public:
    long long maxScore(vector<int>& prices) {
        typedef long long LL;
        int n = prices.size();
        LL ans = 0;
        unordered_map<int, LL> ctr;
        for(int i = 0; i < n; ++i)
            ans = max(ans, ctr[prices[i] - i] += prices[i]);
        return ans;
    }
};
