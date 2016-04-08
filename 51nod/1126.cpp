#include <cstdio>
const int maxn = 52, mod = 7, maxs = mod * mod;
int a, b, n, f[maxn], idx[maxs];
int main()
{
    scanf("%d%d%d", &a, &b, &n);
    f[1] = f[2] = 1;
    idx[f[1] * mod + f[2]] = 2;
    for(int i = 3; i < maxn; ++i)
    {
        f[i] = (a * f[i - 1] + b * f[i - 2]) % mod;
        if(f[i] < 0)
            f[i] += mod;
        if(i == n)
        {
            printf("%d\n", f[i]);
            break;
        }
        if(idx[f[i - 1] * mod + f[i]])
        {
            int sz1 = idx[f[i - 1] * mod + f[i]], sz2 = i - sz1;
            printf("%d\n", f[(n - sz1) % sz2 + sz1]);
            break;
        }
        idx[f[i - 1] * mod + f[i]] = i;
    }
    return 0;
}
