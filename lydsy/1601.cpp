/*
 * 建水库即和0连一条边
 * MST即可
 */
#include <cstdio>
#include <algorithm>
using namespace std;
struct Line { int u, v, w; } line[45150];
int n, m, fa[301], ans = 0;
bool cmp(const Line &x, const Line &y) { return x.w < y.w; }
int find(int x) { if(x == fa[x]) return x; return fa[x] = find(fa[x]); }
int main()
{
    int i, j, k, tmp;
    scanf("%d", &n);
    m = n * (n + 1) / 2;
    for(i = 0; i < n; ++i)
    {
        scanf("%d", &line[i].w);
        line[i].u = i + 1; line[i].v = 0;
        fa[i] = i;
    }
    fa[n] = n;
    for(j = 1; i < m; ++j)
    {
        for(k = 1; k <= j; ++k) scanf("%d", &tmp);
        for(k = j; k < n; ++k, ++i)
        {
            scanf("%d", &line[i].w);
            line[i].u = j; line[i].v = k + 1;
        }
    }
    sort(line, line + m, cmp);
    for(i = 0, tmp = 0; i < m && tmp < n; ++i)
    {
        j = find(line[i].u); k = find(line[i].v);
        if(j != k)
        {
            fa[j] = k;
            ans += line[i].w; ++tmp;
        }
    }
    printf("%d\n", ans);
    return 0;
}
