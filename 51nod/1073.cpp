#include <cstdio>
int n, k, ans;
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 2; i <= n; ++i)
        ans = (ans + k) % i;
    printf("%d\n", ans + 1);
    return 0;
}
