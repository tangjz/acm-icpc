class Solution {
public:
    int numberOfArrays(string s, int k) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        auto mod_inc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        int n = (int)s.length();
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '0')
                continue;
            LL cur = 0;
            for(int j = i; j < n; ++j) {
                cur = cur * 10 + (s[j] - '0');
                if(cur > k)
                    break;
                mod_inc(dp[j + 1], dp[i]);
            }
        }
        return dp[n];
    }
};
