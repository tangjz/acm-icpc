/*
 * 边数与点数的讨论: 
 * 1.点数等于边数，外向树+环形态，环上点必须选环上边，树上方案唯一，总两种方案 
 * 2.点数等于边数+1，树形态，有一个点单独，总点数种方案 
 * 3.其他情况没有解 
 * 分别考虑每个连通块，答案乘起来即可 
 */ 
#include <cstdio>
#include <vector>
using namespace std;
const int mod = 1000000007;
int n, m, nn, mm, ans = 1;
vector<int> edge[100001];
bool vis[100001];
void dfs(int x)
{
	if(vis[x]) return;
	vis[x] = 1;
	int Size = edge[x].size();
	++nn;
	mm += Size;
	for(int i = 0; i < Size; ++i) dfs(edge[x][i]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, u, v; i < m; ++i)
	{
		scanf("%d%d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i)
	{
		if(vis[i] || edge[i].empty()) continue;
		nn = mm = 0;
		dfs(i);
		mm >>= 1;
		if(nn == mm + 1) ans = (long long)ans * nn % mod;
		else if(nn == mm) ans = (ans << 1) % mod;
		else ans = 0;
	}
	printf("%d\n", ans);
	return 0;
}
