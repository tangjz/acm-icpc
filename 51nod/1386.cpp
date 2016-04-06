#include <cstdio>
#include <cstring>
const int maxn = 1001;
int t, n, k, tot, prime[maxn], mid, a[6], cnt, pre[maxn], match[maxn], ans;
bool vis[maxn], fin[maxn];
struct Edge
{
	int nxt, v;
} e[maxn << 1];
void AddEdge(int u, int v)
{
	e[cnt] = (Edge){pre[u], v};
	pre[u] = cnt++;
	//e[cnt] = (Edge){pre[v], u};
	//pre[v] = cnt++;
}
bool path(int u)
{
	for(int it = pre[u]; it != -1; it = e[it].nxt)
		if(!vis[e[it].v])
		{
			vis[e[it].v] = 1;
			if(match[e[it].v] == -1 || path(match[e[it].v]))
			{
				match[e[it].v] = u;
				return 1;
			}
		}
	return 0;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		tot = a[0] = cnt = ans = 0;
		memset(vis, 0, sizeof vis);
		memset(pre, -1, sizeof pre);
		memset(match, -1, sizeof match);
		scanf("%d%d", &n, &k);
		if(n == 1)
		{
			printf("Case #%d: 0\n", Case);
			continue;
		}
		for(int i = 2; i <= n; ++i)
		{
			if(!vis[i])
			{
				if(k % i == 0)
					a[++a[0]] = tot;
				prime[tot++] = i;
			}
			for(int j = 0; j < tot && i * prime[j] <= n; ++j)
			{
				vis[i * prime[j]] = 1;
				if(i % prime[j] == 0)
					break;
			}
		}
		for(mid = 0; prime[mid] * prime[mid] < n; ++mid);
		for(int i = 0; i < mid; ++i)
			for(int j = mid; j < tot && prime[i] * prime[j] <= n; ++j)
			{
				if(a[0] == 2 && a[1] == i && a[2] == j)
				{
					int tmp = prime[i] * prime[j];
					if(tmp != k || tmp * prime[i] <= n)
						AddEdge(i, j);
				}
				else
					AddEdge(i, j);
			}
		for(int i = 0; i < mid; ++i)
		{
			memset(vis, 0, sizeof vis);
			if((fin[i] = path(i)))
				++ans;
		}
		for(int i = mid - 1, j = 1; i >= 0; --i)
			if(!fin[i])
			{
				if(j * prime[i] <= n)
				{
					if(j > 1)
						++ans;
					j *= prime[i];
				}
				else
					j = prime[i];
			}
		printf("Case #%d: %d\n", Case, tot - ans + (k != 1));
	}
	return 0;
}
