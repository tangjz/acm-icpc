/*
 * 树的最小支配集
 * f[i][0]表示以i为根的子树被覆盖，i上无塔的最小方案（至少选一个儿子有塔）
 * f[i][1]表示以i为根的子树被覆盖，i上有塔的最小方案（儿子是否覆盖皆可）
 * f[i][2]表示以i为根的子树除i外被覆盖的最小方案（儿子全没塔但被覆盖）
 * 还有一种解法是贪心，随便取一个点为根
 * 按照到根的距离(深度)降序枚举每个点，如果没被覆盖则在其父亲节点建站
 * 贪心的正确性非常显然：在该种顺序下，一个仍未被覆盖的点只能被自己覆盖或是父亲覆盖
 * 而在父亲节点建站可以覆盖更多的点，不会使建站数增加
 */
#include <cstdio>
const int maxn = 10001;
int n, f[maxn][3], g[maxn], cnt;
struct Node { int v, nxt; } l[maxn << 1];
inline int min(int a, int b) { return a < b ? a : b; }
void dfs(int u, int fa)
{
	int sum = 0;
	f[u][1] = 1;
	for(int i = g[u]; i; i = l[i].nxt)
	{
		int &v = l[i].v;
		if(v == fa) continue;
		dfs(v, u);
		f[u][1] += min(f[v][0], min(f[v][1], f[v][2]));
		f[u][2] += f[v][0];
		sum += min(f[v][0], f[v][1]);
	}
	f[u][0] = maxn;
	if(!l[g[u]].nxt && u != 1) return;
	for(int i = g[u]; i; i = l[i].nxt)
	{
		int &v = l[i].v;
		if(v == fa) continue;
		f[u][0] = min(f[u][0], f[v][1] + sum - min(f[v][0], f[v][1]));
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		l[++cnt] = (Node){v, g[u]}, g[u] = cnt;
		l[++cnt] = (Node){u, g[v]}, g[v] = cnt;
	}
	dfs(1, 0);
	printf("%d\n", min(f[1][0], f[1][1]));
	return 0;
}
