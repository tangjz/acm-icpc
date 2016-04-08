/*
 * 外向树的连通块个数 
 */
#include <cstdio>
int n, fa[1000001], ans;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main()
{
    int i, j;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i) fa[i] = i;
    for(i = 1; i <= n; ++i) scanf("%d", &j), fa[find(i)] = find(j);
    for(i = 1; i <= n; ++i) ans += i == find(i);
    printf("%d\n", ans);
    return 0;
}
