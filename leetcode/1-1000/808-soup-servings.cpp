class Solution {
public:
    double soupServings(int n) {
        const int maxn = 225;
        static bool vis[maxn][maxn] = {};
        static double dp[maxn][maxn] = {};
        function<double(int, int)> calc = [&](int x, int y) -> double {
            if(x <= 0 && y <= 0)
                return 0.5;
            if(x <= 0 || x >= maxn || y >= maxn)
                return 1;
            if(y <= 0)
                return 0;
            double &ret = dp[x][y];
            if(!vis[x][y]) {
                vis[x][y] = 1;
                ret = (calc(x - 4, y) + calc(x - 3, y - 1) + calc(x - 2, y - 2) + calc(x - 1, y - 3)) / 4;
            }
            return ret;
        };
        n = (n + 24) / 25;
        return calc(n, n);
    }
};
