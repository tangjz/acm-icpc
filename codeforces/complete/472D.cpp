#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
int n, g1[2001][2001], g2[2001][2001], fa[2001], tot, s, dist, vis[2001];
struct Line
{
	int u, v, w;
	bool operator < (const Line &t) const
	{
		return w < t.w;
	}
} line[4000010];
vector<edge> e[2001];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void bfs(int now)
{
	vis[now] = 1;
	g2[s][now] = dist;
	for(vector<edge>::iterator it = e[now].begin(), jt = e[now].end(); it != jt; ++it)
		if(!vis[it -> second])
		{
			dist += it -> first;
			bfs(it -> second);
			dist -= it -> first;
		}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
		{
			scanf("%d", &g1[i][j]);
			if(i != j && g1[i][j]) line[tot++] = (Line){i, j, g1[i][j]};
			else if(g1[i][j])
			{
				puts("NO");
				return 0;
			}
		}
	if(n == 1)
	{
		puts("YES");
		return 0;
	}
	sort(line, line + tot);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	int j = 1;
	for(int i = 0; i < tot; ++i)
	{
		int u = find(line[i].u), v = find(line[i].v), w = line[i].w;
		if(u != v)
		{
			fa[u] = v;
			++j;
			e[line[i].u].push_back(make_pair(w, line[i].v));
			e[line[i].v].push_back(make_pair(w, line[i].u));
			if(j == n) break;
		}
	}
	if(j != n)
	{
		puts("NO");
		return 0;
	}
	memset(g2, 0x3f, sizeof g2);
	for(s = 1; s <= n; ++s)
	{
		bfs(s);
		memset(vis, 0, sizeof vis);
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(g1[i][j] != g2[i][j])
			{
				puts("NO");
				return 0;
			}
	puts("YES");
	return 0;
}
