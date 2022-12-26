#include <cstdio>
int n, a[10001][4], x, y, i;
int main()
{
    scanf("%d", &n);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d%d%d%d", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
        a[i][2] += a[i][0];
        a[i][3] += a[i][1];
    }
    scanf("%d%d", &x, &y);
    for(i = n; i; --i) if(a[i][0] <= x && x <= a[i][2] && a[i][1] <= y && y <= a[i][3]) break;
    printf("%d\n", i ? i : -1);
    return 0;
}
