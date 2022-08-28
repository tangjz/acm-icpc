class Solution {
public:
    string largestNumber(vector<int>& c, int m) {
        const int maxd = 9;
        vector<int> dp(m + 1, INT_MIN);
        dp[0] = 0;
        for(int i = 1; i <= m; ++i)
            for(int j = 0; j < maxd; ++j)
                if(i >= c[j])
                    dp[i] = max(dp[i], dp[i - c[j]] + 1);
        if(dp[m] < 0)
            return "0";
        string ret = "";
        while(m > 0) {
            int pos = -1;
            for(int i = maxd - 1; i >= 0; --i)
                if(m >= c[i] && (pos == -1 || dp[m - c[i]] > dp[m - c[pos]]))
                    pos = i;
            assert(pos != -1);
            ret += '1' + pos;
            m -= c[pos];
        }
        return ret;
    }
};
