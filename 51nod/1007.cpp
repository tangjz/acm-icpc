#include <cstdio>
const int maxn = 110, maxs = 5010;
int n, x, f[maxn][maxs];
int main()
{
    scanf("%d", &n);
    f[0][0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        for(int j = 0; j < maxs; ++j)
        {
            if(!f[i - 1][j])
                continue;
            if(j + x < maxs)
                f[i][j + x] = 1;
            if(j - x >= 0)
                f[i][j - x] = 1;
            else
                f[i][x - j] = 1;
        }
    }
    for(int i = 0; i < maxs; ++i)
        if(f[n][i])
        {
            printf("%d\n", i);
            return 0;
        }
    return 0;
}
