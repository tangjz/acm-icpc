#include <cstdio>
int ans = 1;
void dfs(int x)
{
    if(x == 1) return;
    ans += x >> 1;
    for(int i = 2; i <= x >> 1; ++i) dfs(i);
}
int main()
{
    int n;
    scanf("%d", &n);
    dfs(n);
    printf("%d\n", ans);
}
