#include <cstdio>
int t, n, m;
int main()
{
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case)
    {
        scanf("%d%d", &n, &m);
        int A = (((n >> 1) * (m >> 1) + 1) >> 1) << 2;
        int B = n * m - A;
        printf("Case #%d: %s\n", Case, A == B ? "Draw" : (A > B ? "Ana" : "Bob"));
    }
    return 0;
}
