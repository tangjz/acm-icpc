#include <cstdio>
const int maxn = 1000001;
int n, tot, pre[maxn], cnt[maxn], ans;
struct Edge
{
	int nxt, v;
} e[maxn << 1];
int dfs(int u, int fa)
{
	int sz = 1;
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v, tmp;
		if(v == fa)
			continue;
		sz += dfs(v, u);
	}
	++cnt[sz];
	return sz;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[u], v};
		pre[u] = tot;
		e[++tot] = (Edge){pre[v], u};
		pre[v] = tot;
	}
	dfs(1, -1);
	for(int i = 1; i <= n; ++i)
	{
		if(n % i)
			continue;
		for(int j = i + i; j <= n; j += i)
			cnt[i] += cnt[j];
		if(cnt[i] >= n / i)
			++ans;
	}
	printf("%d\n", ans);
	return 0;
}
