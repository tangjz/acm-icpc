class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        const int INF = 0x3f3f3f3f;
        vector<vector<int> > f(k + 1, vector<int>(2, -INF));
        for(int i = 0; i <= k; ++i)
            f[i][0] = 0;
        for(int x: prices)
            for(int i = 0; i <= k; ++i) {
                for(int j = 0; j < 2; ++j) {
                    if(f[i][j] == -INF)
                        continue;
                    if(i > 0 && j + 1 < 2)
                        f[i - 1][j + 1] = max(f[i - 1][j + 1], f[i][j] - x);
                    if(j > 0)
                        f[i][j - 1] = max(f[i][j - 1], f[i][j] + x);
                }
            }
        return f[0][0];
    }
};
