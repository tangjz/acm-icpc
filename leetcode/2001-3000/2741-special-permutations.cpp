class Solution {
public:
    int specialPerm(vector<int>& A) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = A.size(), sz = 1 << n;
        vector<int> cand(n);
        vector<vector<int> > dp(sz, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            dp[1 << i][i] = 1;
            for(int j = 0; j < n; ++j)
                if(A[i] % A[j] == 0 || A[j] % A[i] == 0)
                    cand[i] |= 1 << j;
        }
        for(int s = 1; s < sz; ++s)
            for(int u = 0; u < n; ++u) {
                if(!dp[s][u])
                    continue;
                for(int v = 0; v < n; ++v)
                    if(cand[u] & ~s & (1 << v)) {
                        int t = s | (1 << v);
                        (dp[t][v] += dp[s][u]) >= mod && (dp[t][v] -= mod);
                    }
            }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            (ans += dp[sz - 1][i]) >= mod && (ans -= mod);
        return ans;
    }
};
