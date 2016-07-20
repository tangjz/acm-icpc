#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 404;
int t, n, m, val[maxn], e[maxn][maxn], match[maxn], ans;
set<int> Hash;
bool vis[maxn];
bool path(int u)
{
	for(int i = 1; i <= e[u][0]; ++i)
	{
		int &v = e[u][i];
		if(!vis[v])
		{
			vis[v] = 1;
			if(match[v] == -1 || path(match[v]))
			{
				match[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		Hash.clear();
		memset(match, -1, sizeof match);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", val + i);
			e[i][0] = 0;
		}
		while(m--)
		{
			int x;
			scanf("%d", &x);
			Hash.insert(x);
		}
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				if(Hash.count(val[i] + val[j]))
				{
					e[i][++e[i][0]] = j;
					e[j][++e[j][0]] = i;
				}
		ans = 0;
		for(int i = 0; i < n; ++i)
		{
			memset(vis, 0, sizeof vis);
			if(path(i))
				++ans;
		}
		printf("%d\n", ans >> 1);
	}
	return 0;
}
