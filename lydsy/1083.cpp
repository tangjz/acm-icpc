/*
 * 大水题kruskal直接搞一下就好了 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
struct Line { int u, v, w; } line[45000];
int n, m, fa[301];
bool cmp(const Line &x, const Line &y) { return x.w < y.w; }
int find(int x) { if(x == fa[x]) return x; return fa[x] = find(fa[x]); }
int main()
{
	int i, j, u, v;
	scanf("%d%d", &n, &m);
	for(i = 0; i < m; ++i) scanf("%d%d%d", &line[i].u, &line[i].v, &line[i].w);
	sort(line, line + m, cmp);
	for(i = 1; i <= n; ++i) fa[i] = i;
	for(i = 0, j = 0; i < m; ++i)
	{
		u = find(line[i].u);
		v = find(line[i].v);
		if(u != v)
		{
			fa[u] = v;
			++j;
		}
		if(j == n - 1) break;
	}
	printf("%d %d\n", n - 1, line[i].w);
	return 0;
}
