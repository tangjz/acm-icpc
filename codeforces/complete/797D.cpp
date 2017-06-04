#include <cstdio>
#include <algorithm>
const int maxn = 100001;
int n, val[maxn], cL[maxn], cR[maxn], ord[maxn], tot, in[maxn], out[maxn], bit[maxn], ans;
bool vis[maxn];
void dfs(int u)
{
	if(u == -1)
		return;
	in[u] = ++tot;
	dfs(cL[u]);
	dfs(cR[u]);
	out[u] = tot;
}
void bit_add(int x, int v)
{
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int bit_sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
bool cmp(int const &x, int const &y)
{
	return val[x] < val[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d", val + i, cL + i, cR + i);
		if(cL[i] != -1)
			vis[cL[i]] = 1;
		if(cR[i] != -1)
			vis[cR[i]] = 1;
		ord[i] = i;
	}
	std::sort(ord + 1, ord + n + 1, cmp);
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs(i);
	for(int i = 1; i <= n; ++i)
		if(cR[i] != -1)
		{
			bit_add(in[cR[i]], 1);
			bit_add(out[cR[i]] + 1, -1);
		}
	for(int i = 1, j = 1; i <= n; )
	{
		for( ; j <= n && val[ord[j]] <= val[ord[i]]; ++j)
		{
			int u = ord[j];
			if(cL[u] != -1)
			{
				bit_add(in[cL[u]], 1);
				bit_add(out[cL[u]] + 1, -1);
			}
			if(cR[u] != -1)
			{
				bit_add(in[cR[u]], -1);
				bit_add(out[cR[u]] + 1, 1);
			}
		}
		int cnt = 0, flg = 0;
		for(int v = val[ord[i]]; i <= n && val[ord[i]] == v; ++i, ++cnt)
			flg |= !bit_sum(in[ord[i]]);
		if(!flg)
			ans += cnt;
	}
	printf("%d\n", ans);
	return 0;
}
