class Solution {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        vector<vector<vector<bool> > > f(n + 1, vector<vector<bool> >(n, vector<bool>(n)));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                f[1][i][j] = s1[i] == s2[j];
        for(int i = 2; i <= n; ++i)
            for(int u = 0; u <= n - i; ++u)
                for(int v = 0; v <= n - i; ++v)
                    for(int j = 1; j < i; ++j) {
                        f[i][u][v] = f[j][u][v] && f[i - j][u + j][v + j];
                        if(f[i][u][v])
                            break;
                        f[i][u][v] = f[j][u][v + i - j] && f[i - j][u + j][v];
                        if(f[i][u][v])
                            break;
                    }
        return f[n][0][0];
    }
};
