#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 200010;
const double eps = 1e-8;
inline int dcmp(double x)
{
    return (x > eps) - (x < -eps);
}
struct Point
{
    int id;
    double x, y;
    bool operator < (const Point &t) const
    {
        return dcmp(x - t.x) ? dcmp(x - t.x) < 0 : dcmp(y - t.y) < 0;
    }
    Point operator - (const Point &t) const
    {
        return (Point){0, x - t.x, y - t.y};
    }
    double det(const Point &t) const
    {
        return x * t.y - y * t.x;
    }
} p[maxn];
int n, top, que[maxn], ok[maxn], ans[maxn];
int main()
{
    scanf("%d", &n);
    for(int i = 0, x, y; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        p[i].x = 10000.0 / x;
        p[i].y = 10000.0 / y;
        p[i].id = i + 1;
    }
    sort(p, p + n);
    for(int i = 0; i < n; ++i)
    {
        if(i && !dcmp(p[i].x - p[i - 1].x))
            continue;
        while(top > 1 && dcmp((p[que[top - 1]] - p[que[top - 2]]).det(p[i] - p[que[top - 2]])) < 0)
            --top;
        que[top++] = i;
    }
    for(int i = 0; i < top; ++i)
        if(!i || dcmp(p[que[i]].y - p[que[i - 1]].y) < 0)
            ok[que[i]] = 1;
    for(int i = 0; i < n; ++i)
    {
        if(i && !dcmp(p[i].x - p[i - 1].x) && !dcmp(p[i].y - p[i - 1].y))
            ok[i] |= ok[i - 1];
        if(ok[i])
            ans[p[i].id] = 1;
    }
    for(int i = 1; i <= n; ++i)
        if(ans[i])
            printf("%d ", i);
    puts("");
    return 0;
}
