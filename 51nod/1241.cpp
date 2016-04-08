#include <stdio.h>
const int maxn = 50001;
int n, x, f[maxn], ans;
int main()
{
    scanf("%d", &n);
    for(int i = 1, j; i <= n; ++i)
    {
        scanf("%d", &x);
        f[x] = f[x - 1] + 1;
        if(ans < f[x])
            ans = f[x];
    }
    printf("%d\n", n - ans);
    return 0;
}
