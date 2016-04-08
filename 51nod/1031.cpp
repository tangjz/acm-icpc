#include <cstdio>
const int maxn = 1001, mod = 1000000007;
int n, f[maxn];
int main()
{
    f[0] = f[1] = 1;
    for(int i = 2; i < maxn; ++i)
    {
        f[i] = f[i - 1] + f[i - 2];
        if(f[i] >= mod)
            f[i] -= mod;
    }
    scanf("%d", &n);
    printf("%d\n", f[n]);
    return 0;
}
