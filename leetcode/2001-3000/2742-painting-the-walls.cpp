class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        static const int maxn = 1001, INF = 0x3f3f3f3f;
        int n = cost.size();
        static int f[2][maxn], cur = 0, pre = 1;
        memset(f[cur], 0x3f, (n << 1 | 1) * sizeof(int));
        f[cur][n] = 0;
        auto upd = [&](int &x, int y) {
            x > y && (x = y);
        };
        for(int i = 0; i < n; ++i) {
            swap(pre, cur);
            memset(f[cur], 0x3f, (n << 1 | 1) * sizeof(int));
            for(int j = 0; j <= n + n; ++j) {
                if(f[pre][j] == INF)
                    continue;
                if(j > 0)
                    upd(f[cur][j - 1], f[pre][j]);
                upd(f[cur][min(j + time[i], n + n)], f[pre][j] + cost[i]);
            }
        }
        int ans = INF;
        for(int i = n; i <= n + n; ++i)
            ans = min(ans, f[cur][i]);
        return ans;
    }
};
