/*
 * Burnside定理和Pólya计数法
 * f[i][j][k] = f[i-g[t]][j][k] + f[i][j-g[t]][k] + f[i][j][k-g[t]]
 * ans = sigma(f[sr][sb][sg] / m) % p
 */
#include <cstring>
#include <iostream>
using namespace std;
int n, m, sr, sb, sg, p, g[70][70] = {}, s[70] = {}, f[70][70][70], ans = 0;
bool flag[70];
void gcd(int a, int b, int &x, int &y)
{
    if(!b) { x = 1; y = 0; return; }
    gcd(b, a % b, y, x);
    y -= x * (a / b);
}
int dp(int x)
{
    int i, j, k, l, cnt = 0, tmp;
    memset(flag, false, sizeof(flag));
    memset(f, 0, sizeof(f));
    for(i = 1; i <= n; ++i)
        if(!flag[i])
        {
            s[++cnt] = 1;
            flag[i] = true;
            tmp = i;
            while(!flag[g[x][tmp]])
            {
                flag[g[x][tmp]] = true;
                ++s[cnt];
                tmp = g[x][tmp];
            }
        }
    f[0][0][0] = 1;
    for(l = 1; l <= cnt; ++l)
        for(i = sr; i >= 0; --i)
            for(j = sb; j >= 0; --j)
                for(k = sg; k >= 0; --k)
                {
                    if(i >= s[l]) f[i][j][k] += f[i - s[l]][j][k];
                    if(j >= s[l]) f[i][j][k] += f[i][j - s[l]][k];
                    if(k >= s[l]) f[i][j][k] += f[i][j][k - s[l]];
                    f[i][j][k] %= p;
                }
    return f[sr][sb][sg];
}
int main()
{
    int i, j, x, y;
    ios::sync_with_stdio(false);
    cin >> sr >> sb >> sg >> m >> p;
    n = sr + sb + sg; ++m;
    for(i = 1; i < m; ++i)
        for(j = 1; j <= n; ++j) cin >> g[i][j];
    for(i = 1; i <= n; ++i) g[m][i] = i;
    for(i = 1; i <= m; ++i) ans = (ans + dp(i)) % p;
    gcd(m, p, x, y);
    ans = (ans * (x + p)) % p;
    cout << ans << endl;
    return 0;
}
