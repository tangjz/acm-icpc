#include <cstdio>
#include <algorithm>
using namespace std;
const double eps = 1e-9;
const int maxn = 100010;
int n, A, B, sb;
double sa, ans[maxn];
int sgn(double x)
{
    return (x > eps) - (x < -eps);
}
struct Node
{
    int id, g, a, b;
    bool operator < (const Node &x) const
    {
        return a * x.b > x.a * b;
    }
} p[maxn];
int main()
{
    freopen("burrito.in", "r", stdin);
    freopen("burrito.out", "w", stdout);
    scanf("%d%d%d", &n, &A, &B);
    for(int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &p[i].g, &p[i].a, &p[i].b);
        p[i].id = i;
    }
    sort(p, p + n);
    for(int i = 0; i < n; ++i)
        if(p[i].g * p[i].b + sb <= B)
        {
            ans[p[i].id] = p[i].g;
            sa += p[i].g * p[i].a;
            sb += p[i].g * p[i].b;
        }
        else
        {
            ans[p[i].id] = (double)(B - sb) / p[i].b;
            sa += ans[p[i].id] * p[i].a;
            sb = B;
        }
    if(sgn(A - sa) > 0)
        puts("-1 -1");
    else
    {
        printf("%.9f %d\n", sa, sb);
        for(int i = 0; i < n; ++i)
            printf("%.9f%c", ans[i], " \n"[i == n - 1]);
    }
    return 0;
}
