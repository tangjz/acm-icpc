#include <cstdio>
#include <cstring>
const int maxp = 601;
int n, p1, p2, fa[maxp], dist[maxp], cnt[maxp][2], f[maxp][maxp], pre[maxp][maxp];
bool vis[maxp][2];
int find(int x)
{
	if(x == fa[x])
		return x;
	int tmp = fa[x];
	fa[x] = find(fa[x]);
	dist[x] ^= dist[tmp];
	return fa[x];
}
int main()
{
	while(scanf("%d%d%d", &n, &p1, &p2) == 3 && n + p1 + p2)
	{
		memset(f, 0, sizeof f);
		memset(vis, 0, sizeof vis);
		memset(pre, 0, sizeof pre);
		memset(cnt, 0, sizeof cnt);
		memset(dist, 0, sizeof dist);
		for(int i = 1; i <= p1 + p2; ++i)
			fa[i] = i;
		while(n--)
		{
			int x, y, u, v;
			char op[5];
			scanf("%d%d%s", &x, &y, op);
			if((u = find(x)) != (v = find(y)))
			{
				fa[u] = v;
				dist[u] = dist[x] ^ dist[y] ^ (op[0] == 'n');
			}
		}
		for(int i = 1; i <= p1 + p2; ++i)
		{
			int j = find(i);
			++cnt[j][dist[i]];
		}
		f[0][0] = 1;
		for(int i = 1; i <= p1 + p2; ++i)
			if(!cnt[i][0] && !cnt[i][1])
				for(int j = 0; j <= p1; ++j)
				{
					f[i][j] = f[i - 1][j];
					pre[i][j] = pre[i - 1][j];
				}
			else
				for(int j = 0; j <= p1; ++j)//非好即坏 
				{
					if(j >= cnt[i][0] && f[i - 1][j - cnt[i][0]])
					{
						f[i][j] += f[i - 1][j - cnt[i][0]];
						pre[i][j] = i + i;
					}
					if(j >= cnt[i][1] && f[i - 1][j - cnt[i][1]])
					{
						f[i][j] += f[i - 1][j - cnt[i][1]];
						pre[i][j] = i + i + 1;
					}
				}
		if(f[p1 + p2][p1] != 1)
		{
			puts("no");
			continue;
		}
		for(int i = p1 + p2, j = p1; i > 0 && j > 0; --i)
		{
			int ii = pre[i][j] >> 1, jj = pre[i][j] & 1;
			if(!ii && !jj)
				break;
			vis[ii][jj] = 1;
			i = ii;
			j -= cnt[ii][jj];
		}
		for(int i = 1; i <= p1 + p2; ++i)
			if(vis[find(i)][dist[i]])
				printf("%d\n", i);
		puts("end");
	}
	return 0;
}