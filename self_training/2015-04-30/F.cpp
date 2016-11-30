#pragma comment(linker, "/STACK:16777216")
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, s[maxn];
long long f[maxn], ans;
vector<int> e[maxn];
void pfs(int u, int p)
{
	s[u] = f[u] = 0;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int &v = *it;
		if(v == p)
			continue;
		pfs(v, u);
		s[u] += s[v];
		f[u] += f[v];
	}
	f[u] += s[u];
	++s[u];
}
void dfs(int u, int p)
{
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int &v = *it;
		if(v == p)
			continue;
		f[v] = f[u] + n - s[v] * 2;
		dfs(v, u);
	}
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
			e[i].clear();
		for(int i = 1; i < n; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		pfs(1, -1);
		dfs(1, -1);
		ans = (long long)n * (n - 1) * (n - 2) / 3;
		for(int i = 1; i <= n; ++i)
			ans -= f[i] - (n - 1);
		printf("%I64d\n", ans / 2);
	}
	return 0;
}
