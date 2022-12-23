class Solution {
public:
    int unSuitability(vector<int>& operate) {
        // dp[i][j] -> k (j + j <= k)
        // +x: [max(j-x, 0)]: max(x-j, 0) + k
        // -x: [j+x]: max(x-k+j, 0) + k
        static const int maxv = (int)1e3 + 1, INF = 0x3f3f3f3f;
        int n = operate.size(), m = 0;
        static int f[2][maxv], cur = 1, pre = 0;
        auto clr = [&](int arr[maxv]) {
            memset(arr, 0x3f, (m + 1) * sizeof(int));
        };
        f[cur][0] = 0;
        for(int x: operate) {
            int pm = m;
            m = max(m, x);
            swap(cur, pre);
            clr(f[cur]);
            for(int i = 0; i <= pm; ++i) {
                if(f[pre][i] == INF)
                    continue;
                int L = i, R = f[pre][i] - i;
                {
                    int u = max(L - x, 0), v = R + x;
                    if(u > v)
                        swap(u, v);
                    f[cur][u] = min(f[cur][u], u + v);
                }
                {
                    int u = L + x, v = max(R - x, 0);
                    if(u > v)
                        swap(u, v);
                    f[cur][u] = min(f[cur][u], u + v);
                }
            }
        }
        int ans = INF;
        for(int i = 0; i <= m; ++i)
            ans = min(ans, f[cur][i]);
        return ans;
    }
};
