#include <stdio.h>
#include <algorithm>
using namespace std;
int a, b;
int main()
{
    scanf("%d%d", &a, &b);
    printf("%d\n", __gcd(a, b));
    return 0;
}
