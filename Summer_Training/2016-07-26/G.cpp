#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 51, mod = 1000000007;
int t, n, m, f[2][2][2][2], (*g)[2][2] = f[0], (*h)[2] = g[0], pre = 1, cur, ans;
bool e[maxn][maxn];
int main()
{
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case)
    {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i)
        {
            int k, x;
            memset(e[i], 0, n * sizeof(bool));
            scanf("%d", &k);
            while(k--)
            {
                scanf("%d", &x);
                e[i][--x] = 1;
            }
        }
        ans = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                for(int k = j + 1; k < n; ++k)
                {
                    memset(f[cur], 0, sizeof f[cur]);
                    f[cur][0][0][0] = 1;
                    for(int o = 0; o < m; ++o)
                    {
                        cur ^= 1;
                        pre ^= 1;
                        memcpy(f[cur], f[pre], sizeof f[pre]);
                        int di = e[o][i], dj = e[o][j], dk = e[o][k];
                        for(int x = 0; x < 2; ++x)
                            for(int y = 0; y < 2; ++y)
                                for(int z = 0; z < 2; ++z)
                                    if((f[cur][x][y][z] += f[pre][x ^ di][y ^ dj][z ^ dk]) >= mod)
                                        f[cur][x][y][z] -= mod;
                    }
                    ans = (ans + 6LL * f[cur][1][1][1]) % mod;
                }
                memset(g[cur], 0, sizeof g[cur]);
                g[cur][0][0] = 1;
                for(int o = 0; o < m; ++o)
                {
                    cur ^= 1;
                    pre ^= 1;
                    memcpy(g[cur], g[pre], sizeof g[pre]);
                    int di = e[o][i], dj = e[o][j];
                    for(int x = 0; x < 2; ++x)
                        for(int y = 0; y < 2; ++y)
                            if((g[cur][x][y] += g[pre][x ^ di][y ^ dj]) >= mod)
                                g[cur][x][y] -= mod;
                }
                ans = (ans + 6LL * g[cur][1][1]) % mod;
            }
            memset(h[cur], 0, sizeof h[cur]);
            h[cur][0] = 1;
            for(int o = 0; o < m; ++o)
            {
                cur ^= 1;
                pre ^= 1;
                memcpy(h[cur], h[pre], sizeof h[pre]);
                int di = e[o][i];
                for(int x = 0; x < 2; ++x)
                    if((h[cur][x] += h[pre][x ^ di]) >= mod)
                        h[cur][x] -= mod;
            }
            if((ans += h[cur][1]) >= mod)
                ans -= mod;
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
