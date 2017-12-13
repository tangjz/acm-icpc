#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 51, maxm = maxn * maxn;
int n, m, dsu[maxm], que[maxm], dis[maxm], L, R;
char str[maxn][maxn];
vector<int> e[maxm];
int find(int x)
{
	return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
}
inline int idx(int i, int j)
{
	return i * m + j;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", str[i]);
		for(int j = 0; j < m; ++j)
		{
			dsu[idx(i, j)] = idx(i, j);
			if(i && str[i - 1][j] == str[i][j])
				dsu[find(idx(i - 1, j))] = idx(i, j);
			if(j && str[i][j - 1] == str[i][j])
				dsu[find(idx(i, j - 1))] = idx(i, j);
		}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
		{
			if(i && str[i - 1][j] != str[i][j])
			{
				int u = find(idx(i - 1, j)), v = find(idx(i, j));
				e[u].push_back(v);
				e[v].push_back(u);
			}
			if(j && str[i][j - 1] != str[i][j])
			{
				int u = find(idx(i, j - 1)), v = find(idx(i, j));
				e[u].push_back(v);
				e[v].push_back(u);
			}
		}
	for(int i = 0; i < n * m; ++i)
	{
		sort(e[i].begin(), e[i].end());
		unique(e[i].begin(), e[i].end());
	}
	int ans = n * m;
	for(int i = 0; i < n * m; ++i)
	{
		if(find(i) != i)
			continue;
		memset(dis, 0, n * m * sizeof(int));
		L = R = 0;
		dis[i] = 1;
		que[R++] = i;
		while(L < R)
		{
			int u = que[L++];
			for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = *it;
				if(!dis[v])
				{
					dis[v] = dis[u] + 1;
					que[R++] = v;
				}
			}
		}
		int x = que[R - 1] / m, y = que[R - 1] % m, tmp = dis[que[R - 1]] - (str[x][y] == 'W');
		if(ans > tmp)
			ans = tmp;
	}
	printf("%d\n", ans);
	return 0;
}
