#include <cstdio>
#include <cstring>
const int maxn = 1200001;
int n, fa[maxn], tot, pre[maxn], cnt[maxn], ans;
struct Edge
{
	int nxt, v;
} e[maxn];
int dfs(int u)
{
	int sz = 1;
	for(int it = pre[u]; it; it = e[it].nxt)
		sz += dfs(e[it].v);
	++cnt[sz];
	return sz;
}
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i)
		scanf("%d%*c", fa + i);
	for(int Case = 1; Case <= 10; ++Case)
	{
		tot = 0;
		memset(pre + 1, 0, n * sizeof(int));
		memset(cnt + 1, 0, n * sizeof(int));
		for(int i = 2; i <= n; ++i)
		{
			int u = fa[i], v = i;
			e[++tot] = (Edge){pre[u], v};
			pre[u] = tot;
		}
		dfs(1);
		printf("Case #%d:\n", Case);
		for(int i = 1; i <= n; ++i)
		{
			if(n % i)
				continue;
			for(int j = i + i; j <= n; j += i)
				cnt[i] += cnt[j];
			if(cnt[i] >= n / i)
				printf("%d\n", i);
		}
		if(Case < 10)
			for(int i = 2; i <= n; ++i)
				fa[i] = (fa[i] + 19940105) % (i - 1) + 1;
	}
	return 0;
}
