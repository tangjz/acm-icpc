#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 111;
int n, tot_r, tot_c, rid[maxn][maxn], cid[maxn][maxn], match[maxn * maxn], ans;
char str[maxn][maxn];
vector<int> e[maxn * maxn];
bool vis[maxn * maxn];
bool path(int u)
{
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int &v = *it;
		if(vis[v])
			continue;
		vis[v] = 1;
		if(!match[v] || path(match[v]))
		{
			match[v] = u;
			return 1;
		}
	}
	return 0;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		tot_r = tot_c = ans = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%s", str[i] + 1);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
			{
				if(str[i][j] != '.')
					continue;
				if(str[i][j - 1] != '.')
					++tot_r;
				rid[i][j] = tot_r;
			}
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
			{
				if(str[j][i] != '.')
					continue;
				if(str[j - 1][i] != '.')
					++tot_c;
				cid[j][i] = tot_c;
			}
		ans = 0;
		for(int i = 1; i <= tot_r; ++i)
			e[i].clear();
		memset(match + 1, 0, tot_c * sizeof(int));
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
			{
				if(str[i][j] != '.')
					continue;
				e[rid[i][j]].push_back(cid[i][j]);
			}
		for(int i = 1; i <= tot_r; ++i)
		{
			memset(vis + 1, 0, tot_c * sizeof(bool));
			if(path(i))
				++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
