/*
 * 博弈的策略类似于dp 
 */
#include <cstdio>
#include <algorithm>
int n, i;
long long f[1000001];
int main()
{
    scanf("%d", &n);
    for(i = 0; i < n; ++i) scanf("%lld", &f[i]);
    std::sort(f, f + n);
    for(i = 1; i < n; ++i) f[i] = std::max(f[i - 1], f[i] - f[i - 1]);
    printf("%lld\n", f[n - 1]);
}
