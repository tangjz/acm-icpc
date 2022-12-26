/*
 * 汉诺塔移动步数满足 Fn = A * Fn-1 + B
 * 暴力出 F[1] = 1, F[2], F[3]
 * A = (f[3] - f[2]) / (f[2] - f[1])   B = f[2] - A * f[1]
 * 递推F(n)
 */
#include <cstdio>
#include <iostream>
using namespace std;
int n, way[6][2] = {}, q[3][4] = {};
long long A, B, tmp, ans;
int dfs(int n)
{
    int i, last = -1, x, y, cnt = 0;
    q[0][0] = n;
    for(i = 1; i <= n; ++i) q[0][i] = n - i + 1;
    q[1][0] = q[2][0] = 0;
    while(1)
    {
        ++cnt;
        for(i = 0; i < 6; ++i)
        {
            x = way[i][0];
            y = way[i][1];
            if(x != last && q[x][0] && (!q[y][0] || q[x][q[x][0]] < q[y][q[y][0]]))
            {
                last = y;
                q[y][++q[y][0]] = q[x][q[x][0]--];
                break;
            }
        }
        if(q[1][0] == n || q[2][0] == n) break;
    }
    return cnt;
}
int main()
{
    int i;
    char ch;
    scanf("%d", &n);
    for(i = 0; i < 6; ++i)
    {
        ch = getchar();
        while(ch < 'A' || ch > 'C') ch = getchar();
        way[i][0] = ch - 'A';
        way[i][1] = getchar() - 'A';
    }
    if(n == 1) printf("1\n");
    else if(n <= 3) printf("%d\n", dfs(n));
    else
    {
        tmp = dfs(2);
        if(tmp == 5) ans = 17;
        else ans = dfs(3);
        A = (ans - tmp) / (tmp - 1);
        B = tmp - A;
        for(i = 4; i <= n; ++i) ans = A * ans + B;
        printf("%lld\n", ans);
    }
    return 0;
}
