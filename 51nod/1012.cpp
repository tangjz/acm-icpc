#include <stdio.h>
#include <algorithm>
using namespace std;
int a, b;
int main()
{
    scanf("%d%d", &a, &b);
    printf("%lld\n", (long long)a / __gcd(a, b) * b);
    return 0;
}
