#include <cstdio>
int n, ans;
void dfs(int l, int r)
{
	if(l == r)
		return;
	if(r - l == 1)
		ans += l * r;
	int m = l + r >> 1;
	dfs(l, m);
	dfs(m + 1, r);
}
int main()
{
	scanf("%d", &n);
	dfs(1, n);
	printf("%d\n", ans);
	return 0;
}
