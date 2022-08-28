class Solution {
    string compress(int L, int R, string &s, vector<vector<pair<int, int> > > &dp) {
        if(L == R)
            return s.substr(L, 1);
        if(dp[L][R].second <= 0) {
            int M = -dp[L][R].second;
            return compress(L, M, s, dp) + compress(M + 1, R, s, dp);
        }
        int d = dp[L][R].second, x = R - (R - L + 1) / d + 1;
        return to_string(d) + "[" + compress(x, R, s, dp) + "]";
    }
public:
    string encode(string s) {
        int n = s.size();
        vector<vector<int> > lcs(n, vector<int>(n));
        vector<vector<pair<int, int> > > dp(n, vector<pair<int, int> >(n, {INT_MAX, -1}));
        for(int i = 0; i < n; ++i) {
            dp[i][i] = {1, 1};
            for(int j = 0; j < n; ++j)
                if(s[i] == s[j])
                    lcs[i][j] = (i && j ? lcs[i - 1][j - 1] : 0) + 1;
        }
        for(int len = 2; len <= n; ++len) {
            vector<pair<int, int> > fct;
            for(int i = 2; i <= len; ++i)
                if(len % i == 0)
                    fct.push_back({len / i, to_string(i).size()});
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                for(int M = L; M < R; ++M)
                    dp[L][R] = min(dp[L][R], make_pair(dp[L][M].first + dp[M + 1][R].first, -M));
                for(auto &it: fct)
                    if(lcs[R - it.first][R] >= len - it.first)
                        dp[L][R] = min(dp[L][R], make_pair(dp[R - it.first + 1][R].first + it.second + 2, len / it.first));
            }
        }
        return compress(0, n - 1, s, dp);
    }
};
