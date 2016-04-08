#include <cstdio>
int n;
int main()
{
    while(scanf("%d", &n) == 1)
        printf("%lld\n", n < 3 ? n : ((n & 1) ? n * (n - 1) * (n - 2) : (n % 3 ? n * (n - 1) * (n - 3) : (n - 1) * (n - 2) * (n - 3))));
    return 0;
}
