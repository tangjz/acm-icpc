#include <cstdio>
typedef long long LL;
const int maxn = 11, maxm = maxn * maxn, mod = 1000000007;
int c[maxn][maxn], pw[maxn * maxn], f[maxn][maxn];
int main()
{
    for(int i = 0; i < maxn; ++i)
    {
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++j)
            if((c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod)
                c[i][j] -= mod;
    }
    pw[0] = 1;
    for(int i = 1; i < maxn * maxn; ++i)
        pw[i] = (LL)pw[i - 1] * 3 % mod;
    for(int i = 1; i < maxn; ++i)
        for(int j = 0; j < maxn; ++j)
        {
            f[i][j] = pw[i * j];
            for(int x = 1; x <= i; ++x)
                for(int y = 0; y <= j; ++y)
                {
                    if(x == i && y == j)
                        continue;
                    if((f[i][j] -= (LL)c[i - 1][x - 1] * c[j][y] % mod * f[x][y] % mod * pw[(i - x) * (j - y)] % mod) < 0)
                        f[i][j] += mod;
                }
        }
    //for(int i = 1; i < maxn; ++i)
    //    for(int j = 1; j < maxn; ++j)
    //        printf("%d%c", f[i][j], " \n"[j == maxn - 1]);
    int n, m;
    while(scanf("%d%d", &n, &m) == 2)
        printf("%d\n", f[n][m]);
    return 0;
}
