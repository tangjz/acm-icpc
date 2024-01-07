#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1000001;
int n, m, a[maxn], b[maxn], fa[maxn];
std::pair<int, int> c[maxn];
std::vector<int> e[maxn];
int find(int x)
{
	return fa[x] < 0 ? x : fa[x] = find(fa[x]);
}
void merge(int u, int v)
{
	if((u = find(u)) == (v = find(v)))
		return;
	if(fa[u] == fa[v])
	{
		fa[v] = u;
		--fa[u];
	}
	else if(fa[u] < fa[v])
		fa[v] = u;
	else
		fa[u] = v;
}
int dfs(int u)
{
	if(b[u])
		return b[u];
	int ret = 0;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		ret = std::max(ret, dfs(*it));
	return b[u] = ret + 1;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n * m; ++i)
		scanf("%d", a + i);
	memset(fa, -1, n * m * sizeof(int));
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
			c[j] = std::make_pair(a[i * m + j], i * m + j);
		std::sort(c, c + m);
		for(int j = 0, k = 0; j < m; j = k)
			for( ; k < m && c[j].first == c[k].first; ++k)
				merge(c[j].second, c[k].second);
	}
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
			c[j] = std::make_pair(a[j * m + i], j * m + i);
		std::sort(c, c + n);
		for(int j = 0, k = 0; j < n; j = k)
			for( ; k < n && c[j].first == c[k].first; ++k)
				merge(c[j].second, c[k].second);
	}
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
			c[j] = std::make_pair(a[i * m + j], i * m + j);
		std::sort(c, c + m);
		for(int j = 0, k = 0; j < m; j = k)
		{
			for( ; k < m && c[j].first == c[k].first; ++k);
			if(j)
				e[find(c[j].second)].push_back(find(c[j - 1].second)); 
		}
	}
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
			c[j] = std::make_pair(a[j * m + i], j * m + i);
		std::sort(c, c + n);
		for(int j = 0, k = 0; j < n; j = k)
		{
			for( ; k < n && c[j].first == c[k].first; ++k);
			if(j)
				e[find(c[j].second)].push_back(find(c[j - 1].second)); 
		}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			printf("%d%c", dfs(find(i * m + j)), " \n"[j == m - 1]);
	return 0;
}
