#include <stdio.h>
int n, x;
long long now, ans = -0x3f3f3f3f;
int main()
{
    scanf("%d", &n);
    while(n--)
    {
        if(now < 0)
            now = 0;
        scanf("%d", &x);
        now += x;
        if(ans < now)
            ans = now;
    }
    printf("%lld\n", ans);
    return 0;
}
