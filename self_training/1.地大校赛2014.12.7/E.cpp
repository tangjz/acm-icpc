#include <cstdio>
long long p, q;
int main()
{
    while(scanf("%lld%lld", &p, &q) == 2)
    {
        if(p == q)
            p += 2;
        p = p - 1 >> 1;
        q = q - 1 >> 1;
        printf("%lld\n", p * q);
    }
    return 0;
}
