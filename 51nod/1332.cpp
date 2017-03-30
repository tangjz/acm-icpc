#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 301;
int t, n, p[maxn], dis[maxn][maxn], pre[maxn][maxn], *Dis, *Pre, ctr, vis[maxn][maxn];
vector<int> e[maxn];
char buf[maxn];
void dfs(int u, int fa)
{
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa)
			continue;
		Dis[v] = Dis[u] + 1;
		Pre[v] = u;
		dfs(v, u);
	}
}
inline bool on_path(int u, int v, int w)
{
	return dis[u][v] + dis[v][w] == dis[u][w];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			vector<int>().swap(e[i]);
		ctr = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%*d%d%d", p + i, vis[0] + i);
			if(p[i] >= 0)
			{
				e[i].push_back(p[i]);
				e[p[i]].push_back(i);
			}
			ctr += !vis[0][i];
		}
		for(int i = 0; i < n; ++i)
		{
			Dis = dis[i];
			Pre = pre[i];
			dfs(i, -1);
		}
		buf[0] = '1';
		for(int i = 1; i < n; ++i)
		{
			buf[i] = '0';
			if(buf[p[i]] == '0')
				continue;
			memcpy(vis[i], vis[p[i]], n * sizeof(int)); // change current state
			for(int j = i; j < n; ++j) // j may be i
				if(on_path(p[i], i, j) && !vis[i][j])
				{
					swap(vis[i][p[i]], vis[i][j]);
					buf[i] = '1';
					break;
				}
			if(buf[i] == '1')
				continue;
			int u = -1; // now, vis[i][p[i]] = vis[i][i] = 1
			for(int j = 0; j < n; ++j)
				if(on_path(i, p[i], j) && !vis[i][j]) // j != p[i]
				{
					if(u == -1)
						u = pre[j][p[i]];
					else if(u != pre[j][p[i]])
					{
						swap(vis[i][p[i]], vis[i][j]);
						buf[i] = '1';
						break;
					}
				}
			if(buf[i] == '1' || u == -1)
				continue;
			int v = -1; // now, all j with vis[i][j] = 0 must have on_path(p[i], u, j) or (p[i], i, j)
			for(int j = 0; j < n; ++j)
				if(on_path(p[i], u, j) && e[j].size() >= 3)
				{
					if(v == -1)
						v = j;
					else if(dis[p[i]][j] < dis[p[i]][v])
						v = j;
				}
			if(v == -1 || ctr < dis[p[i]][v] + 2)
				continue;
			for(int j = 0; j < n; ++j)
				if(on_path(p[i], u, j) && !vis[i][j])
				{
					swap(vis[i][p[i]], vis[i][j]);
					buf[i] = '1';
					break;
				}
		}
		buf[n] = '\0';
		puts(buf);
	}
	return 0;
}
