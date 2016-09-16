#include <stdio.h>
const int mod = 1000000007;
int n, ans;
int main()
{
    scanf("%d", &n);
    ans = n + 1;
    for(int i = 2; i < n; ++i)
        if((ans += ans) >= mod)
            ans -= mod;
    printf("%d\n", ans);
    return 0;
}
