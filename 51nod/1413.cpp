#include <cstdio>
int n, ans;
int main()
{
    scanf("%d", &n);
    while(n)
    {
        if(ans < n % 10)
            ans = n % 10;
        n /= 10;
    }
    printf("%d\n", ans);
    return 0;
}
