#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001;
int t, n, f[maxn];
vector<int> e[maxn];
bool flag[maxn];
void dfs(int u, int p)
{
	f[u] = 1;
	flag[u] = 0;
	int cnt = 0;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(*it == p)
			continue;
		dfs(*it, u);
		f[u] += f[*it];
		if(!flag[*it])
			++cnt;
	}
	if(cnt >= 2)
	{
		f[u] -= 2;
		flag[u] = 1;
	}
	else if(cnt == 1)
		--f[u];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			e[i].clear();
		for(int i = 1; i < n; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		dfs(1, -1);
		printf("%d\n", f[1]);
	}
	return 0;
}
