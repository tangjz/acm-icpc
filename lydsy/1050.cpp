/*
 * 枚举区间[L,R]求出最小的R，反求最大的L，更新答案
 * 继续枚举区间[L + 1, R]，更新 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
struct Line { int u, v, w; } line[50001] = {};
int n, m, s, t, fa[501] = {}, ans_max = 1, ans_min = 0;
bool cmp(const Line &x, const Line &y) { return x.w < y.w; }
int gcd(int a, int b) { if(!b) return a; return gcd(b, a % b); }
int find(int x) { if(x == fa[x]) return x; return fa[x] = find(fa[x]); }
void union_clear() { for(int i = 1; i <= n; ++i) fa[i] = i; }
int main()
{
    int i, j, u, v, max_w, min_w, r, start = 0;
    scanf("%d%d", &n, &m);
    for(i = 0; i < m; ++i) scanf("%d%d%d", &line[i].u, &line[i].v, &line[i].w);
    sort(line, line + m, cmp);
    scanf("%d%d", &s, &t);
    while(start < m)
    {
        min_w = max_w = -1;
        union_clear();
        for(j = start; j < m; ++j)
        {
            u = find(line[j].u); v = find(line[j].v); fa[u] = v;
            if(find(s) == find(t)) { max_w = line[j].w; break; }
        }
        if(max_w == -1)
        {
            if(!ans_min) { printf("IMPOSSIBLE\n"); return 0; }
            else break;
        }
        union_clear();
        for( ; j >= 0; --j)
        {
            u = find(line[j].u); v = find(line[j].v); fa[u] = v;
            if(find(s) == find(t)) { min_w = line[j].w; break; }
        }
        start = j + 1;
        if(min_w == -1)
        {
            if(!ans_min) { printf("IMPOSSIBLE\n"); return 0; }
            else break;
        }
        r = gcd(max_w, min_w); max_w /= r; min_w /= r;
        if(ans_max * min_w > ans_min * max_w) { ans_max = max_w; ans_min = min_w; }
    }
    if(ans_min == 1) printf("%d\n", ans_max);
    else printf("%d/%d\n", ans_max, ans_min);
    return 0;
}
