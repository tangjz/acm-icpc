#include <cstdio>
const int maxn = 1001;
int n, m, p, f[maxn][maxn], g[maxn][maxn];
char s[maxn], t[maxn], q[maxn];
void upd(int a, int b, int c, int d)
{
    if(f[a][b] > f[c][d])
        return;
    f[a][b] = f[c][d];
    g[a][b] = c * maxn + d;
}
int main()
{
    scanf("%s%s", s, t);
    for(n = 0; s[n]; ++n);
    for(m = 0; t[m]; ++m);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
        {
            if(s[i - 1] == t[j - 1])
            {
                upd(i, j, i - 1, j - 1);
                ++f[i][j];
                continue;
            }
            upd(i, j, i - 1, j);
            upd(i, j, i, j - 1);
        }
    p = f[n][m];
    for(int i = n, j = m, ni, nj; f[i][j]; i = ni, j = nj)
    {
        ni = g[i][j] / maxn;
        nj = g[i][j] % maxn;
        if(f[ni][nj] < f[i][j])
            q[--p] = s[i - 1];
    }
    puts(q);
    return 0;
}
