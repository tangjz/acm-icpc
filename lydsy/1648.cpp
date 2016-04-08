#include <cstdio>
#include <cstring>
const int maxn = 1001, maxm = 10001;
int t, n, m, tot, pre[maxn], seq[maxn], que[maxn], L, R, ans;
bool vis[maxn];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
void AddEdge(int u, int v)
{
	e[++tot] = (Edge){pre[u], v};
	pre[u] = tot;
}
int main()
{
	scanf("%d%d%d", &t, &n, &m);
	for(int i = 0; i < t; ++i)
		scanf("%d", seq + i);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		AddEdge(v, u);
	}
	for(int i = 1; i <= n; ++i)
	{
		L = R = 0;
		memset(vis, 0, sizeof vis);
		vis[i] = 1;
		que[R++] = i;
		while(L < R)
		{
			int &u = que[L++];
			for(int it = pre[u]; it; it = e[it].nxt)
				if(!vis[e[it].v])
				{
					vis[e[it].v] = 1;
					que[R++] = e[it].v;
				}
		}
		bool flag = 1;
		for(int j = 0; j < t; ++j)
			if(!vis[seq[j]])
			{
				flag = 0;
				break;
			}
		if(flag)
			++ans;
	}
	printf("%d\n", ans);
	return 0;
}
