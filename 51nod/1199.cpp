#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 50001;
int n, m, tot, lnk[maxn], w[maxn], seq[maxn], in[maxn], out[maxn];
struct Edge {
	int nxt, v;
} e[maxn];
void dfs(int u)
{
	seq[++tot] = u;
	in[u] = tot;
	for(int it = lnk[u]; it; it = e[it].nxt)
		dfs(e[it].v);
	out[u] = tot;
}
LL bit[2][maxn];
void add(int x, int v)
{
	for(int i = x; i <= n; i += i & -i)
	{
		bit[0][i] += v;
		bit[1][i] += (LL)x * v;
	}
}
LL sum(int x)
{
	LL ret = 0;
	for(int i = x; i > 0; i -= i & -i)
		ret += (x + 1) * bit[0][i] - bit[1][i];
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1, j; i < n; ++i)
	{
		scanf("%d%d", &j, w + i);
		e[i] = (Edge){lnk[j], i};
		lnk[j] = i;
	}
	dfs(0);
	for(int i = 1; i <= n; ++i)
	{
		int v = w[seq[i]] - w[seq[i - 1]];
		bit[0][i] += v;
		bit[1][i] += (LL)i * v;
		int j = i + (i & -i);
		if(j <= n)
		{
			bit[0][j] += bit[0][i];
			bit[1][j] += bit[1][i];
		}
	}
	while(m--)
	{
		char op[2];
		int x, y, z;
		scanf("%s%d%d%d", op, &x, &y, &z);
		if(op[0] == 'S')
		{
			if(sum(in[x]) - sum(in[x] - 1) < y)
			{
				add(in[x], z);
				add(in[x] + 1, -z);
			}
		}
		else
		{
			if(sum(out[x]) - sum(in[x] - 1) < y * (out[x] - in[x] + 1LL))
			{
				add(in[x], z);
				add(out[x] + 1, -z);
			}
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		int j = i - (i & -i);
		if(j > 0)
		{
			bit[0][i] += bit[0][j];
			bit[1][i] += bit[1][j];
		}
	}
	for(int i = 1; i <= n; ++i)
		bit[0][i] = (i + 1) * bit[0][i] - bit[1][i];
	for(int i = 0; i < n; ++i)
		printf("%lld\n", bit[0][in[i]] - bit[0][in[i] - 1]);
	return 0;
}
