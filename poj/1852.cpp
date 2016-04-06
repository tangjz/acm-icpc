#include <cstdio>
template<class _> inline const _& max (const _& x, const _& y) { return x < y ? y : x; }
int main()
{
    int t, length, n, pos, dist, ans1, ans2;
    scanf("%d", &t);
    while(t--)
    {
        ans1 = ans2 = 0;
        scanf("%d%d", &length, &n);
        while(n--)
        {
            scanf("%d", &pos);
            dist = max(pos, length - pos);
            ans1 = max(ans1, length - dist);
            ans2 = max(ans2, dist);
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}
