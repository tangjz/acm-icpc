/*
 * 计算相同的就好...
 */
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int ScanInt(void)
{
	int r = 0, c, d;
	while(!isdigit(c = getchar()) && c != '-');
	if(c != '-') r = c - '0'; d = c;
	while(isdigit(c = getchar())) r = r * 10 + c - '0';
	return d == '-' ? -r : r;
}
struct Line{
	int u, v, w;
	bool operator < (const Line &x) const { return w < x.w; }
} edge[200001];
int now, tmp, num, ans, sum, n, m;
struct Union{
	int fa[201];
	void init() { for(int i = 1; i <= n; ++i) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	bool combine(int u, int v) { u = find(u); v = find(v); if (u == v) return false; fa[u] = v; return true; }
} NOW, LAST;
void dfs(int dep, int get)
{
	if (dep == now + 1 && get == tmp){
		++sum; return;
		}
	if (dep == now + 1) return;
	dfs(dep + 1, get);
	Union temp = LAST;
	if (LAST.combine(edge[dep].u, edge[dep].v)) dfs(dep + 1, get + 1);
	LAST = temp;
}
int main()
{
	n = ScanInt(); m = ScanInt();
	for(int i = 1; i <= m; ++i) { edge[i].u = ScanInt(); edge[i].v = ScanInt(); edge[i].w = ScanInt(); }
	sort(edge + 1, edge + m + 1);
	num = 0; ans = 1;
	NOW.init(); LAST.init();
	for(int i = 1; i <= m;)
	{
		now = i; while(now < m && edge[i].w == edge[now + 1].w) ++now;
		tmp = 0; for (int j = i; j <= now; j++) tmp += NOW.combine(edge[j].u, edge[j].v);
		sum = 0; dfs(i, 0); ans = (ans * sum) % 31011;
		num += tmp;
		LAST = NOW;
		i = now + 1;
	}
	if (num != n - 1) puts("0");
	else printf("%d\n", ans);
	return 0;
}
