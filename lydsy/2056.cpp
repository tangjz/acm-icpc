/*
 * 恶心题 注意内存
 * 答案在2^3 ~ 2^64之间 
 * 对于溢出unsigned long long的2^64进行特判输出 
 */
#include <stdio.h>
#include <string.h>
int t, x;
unsigned long long i, ans;
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        ans = 0;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%d", &x); ans += 1ll << x;
        scanf("%Lu", &i); ans += i;
        if(!ans) printf("18446744073709551616\n");
        else printf("%llu\n", ans);
    }
    return 0;
}
