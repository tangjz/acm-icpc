#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, tot, lnk[maxn], rt, in[maxn], out[maxn];
struct Edge {
	int nxt, v;
} e[maxn];
void dfs(int u)
{
	in[u] = ++tot;
	for(int it = lnk[u]; it; it = e[it].nxt)
		dfs(e[it].v);
	out[u] = tot;
}
int rk[maxn], val[maxn], ord[maxn];
LL bit[maxn], ans[maxn];
bool cmp(int const &x, int const &y)
{
	return rk[x] < rk[y];
}
void bit_add(int x, int v)
{
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
LL bit_sum(int x)
{
	LL ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int fa;
		scanf("%d%d%d", &fa, rk + i, val + i);
		ord[i] = i;
		if(fa == -1)
		{
			rt = i;
			continue;
		}
		e[++tot] = (Edge){lnk[fa], i};
		lnk[fa] = tot;
	}
	tot = 0;
	dfs(rt);
	sort(ord + 1, ord + n + 1, cmp);
	for(int i = 1, j = 1; i <= n; ++i)
	{
		for( ; j <= n && rk[ord[j]] < rk[ord[i]]; ++j)
			bit_add(in[ord[j]], val[ord[j]]);
		ans[ord[i]] = bit_sum(out[ord[i]]) - bit_sum(in[ord[i]] - 1);
	}
	for(int i = 1; i <= n; ++i)
		printf("%I64d\n", ans[i]);
	return 0;
}
