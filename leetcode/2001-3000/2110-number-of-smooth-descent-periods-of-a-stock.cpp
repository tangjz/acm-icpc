class Solution {
    typedef long long LL;
public:
    LL getDescentPeriods(vector<int>& prices) {
        int n = prices.size();
        LL ans = 0;
        for(int i = 0, j; i < n; i = j) {
            for(j = i + 1; j < n && prices[j - 1] == prices[j] + 1; ++j);
            int len = j - i;
            ans += len * (len + 1LL) / 2;
        }
        return ans;
    }
};
