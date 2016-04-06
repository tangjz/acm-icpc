#include <cstdio>
#include <cstring>
const int maxn = 100001;
int n, m, fa[maxn], cnt[maxn];
int find(int x)
{
	return fa[x] < 0 ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(fa, -1, sizeof fa);
	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if((u = find(u)) != (v = find(v)))
		{
			fa[u] += fa[v];
			fa[v] = u;
			cnt[u] += cnt[v];
		}
		++cnt[u];
	}
	bool flag = 0;
	for(int i = 1; i <= n; ++i)
		if(fa[i] < 0)
			flag |= -fa[i] == cnt[i] + 1;
	puts(flag ? "NIE" : "TAK");
	return 0;
}
