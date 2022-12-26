#include <stdio.h>
int n;
int main()
{
    while(scanf("%d", &n) == 1)
        puts(n & 1 ? "0" : "1");
    return 0;
}
