class Solution {
public:
    int beautifulPartitions(string s, int k, int m) {
        const int mod = (int)1e9 + 7, maxd = 10;
        int n = s.size();
        vector<bool> pr(maxd), ok(n);
        pr[2] = pr[3] = pr[5] = pr[7] = 1;
        for(int i = 0; i < n; ++i)
            ok[i] = pr[s[i] - '0'];
        if(!ok[0] || ok[n - 1])
            return 0;
        if(k == 1)
            return 1;
        vector<int> pos;
        for(int i = m; i <= n - m; ++i)
            if(!ok[i - 1] && ok[i])
                pos.push_back(i);
        n = pos.size();
        --k;
        vector<int> nxt(n);
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && pos[j] < pos[i] + m; ++j);
            nxt[i] = j;
            // printf("pos %d: %d nxt %d\n", i, pos[i], nxt[i]);
        }
        auto modInc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        vector<vector<int> > dp(n + 1, vector<int>(k + 1));
        dp[0][0] = 1;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < k; ++j) {
                modInc(dp[i + 1][j], dp[i][j]);
                modInc(dp[nxt[i]][j + 1], dp[i][j]);
            }
            modInc(dp[i + 1][k], dp[i][k]);
        }
        return dp[n][k];
    }
};
