class Solution {
public:
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        const int INF = (int)2e9;
        int n = (int)dist.size(), sum = 0, adt = 0, upp = min(1LL * hoursBefore * speed, INF - 1LL);
        for(int x: dist) {
            sum += x;
            int r = x % speed;
            if(r > 0)
                adt += speed - r;
        }
        if(sum + adt <= upp)
            return 0;
        if(sum > upp)
            return -1;
        vector<vector<int> > dp(n + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= i; ++j) {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + dist[i]);
                int dt = dp[i][j] % speed;
                if(dt > 0)
                    dt = speed - dt;
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + dt + dist[i]);
            }
        for(int i = 0; i <= n; ++i)
            if(dp[n][i] <= upp)
                return i;
        assert(false);
    }
};
