#include <bitset>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100000;
int n, m, q, seq[maxn], scnt, sno[maxn], fin[maxn];
vector<int> e[maxn], rev[maxn], query[maxn], se[maxn];
bitset<maxn / 10> msk[maxn];
bool vis[maxn];
void pfs1(int u)
{
	vis[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(!vis[*it])
			pfs1(*it);
	seq[scnt++] = u;
}
void pfs2(int u)
{
	vis[u] = 1;
	sno[u] = scnt;
	for(vector<int>::iterator it = rev[u].begin(); it != rev[u].end(); ++it)
		if(!vis[*it])
			pfs2(*it);
}
void dfs(int u)
{
	vis[u] = 1;
	for(vector<int>::iterator it = se[u].begin(); it != se[u].end(); ++it)
	{
		if(!vis[*it])
			dfs(*it);
		msk[u] |= msk[*it];
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		e[u].push_back(v);
		rev[v].push_back(u);
	}
	scnt = 0;
	memset(vis, 0, n * sizeof(bool));
	for(int i = 0; i < n; ++i)
		if(!vis[i])
			pfs1(i);
	scnt = 0;
	memset(vis, 0, n * sizeof(bool));
	for(int i = n - 1; i >= 0; --i)
		if(!vis[seq[i]])
		{
			pfs2(seq[i]);
			++scnt;
		}
	for(int i = 0; i < n; ++i)
		for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
			if(sno[i] != sno[*it])
				se[sno[i]].push_back(sno[*it]);
	for(int i = 0; i < scnt; ++i)
	{
		sort(se[i].begin(), se[i].end());
		unique(se[i].begin(), se[i].end());
	}
	scanf("%d", &q);
	for(int i = 0; i < q; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		if(sno[u] != sno[v])
			query[sno[u]].push_back(sno[v]);
		else
		{
			puts("NO");
			return 0;
		}
	}
	for(int i = 0; i < scnt; ++i)
	{
		sort(query[i].begin(), query[i].end());
		unique(query[i].begin(), query[i].end());
	}
	bool flag = 1;
	for(int fir = 0; fir < scnt; fir += maxn / 10)
	{
		for(int i = 0; i < scnt; ++i)
			msk[i].reset();
		for(int i = 0; i < maxn / 10 && fir + i < scnt; ++i)
			msk[fir + i].set(i);
		memset(vis, 0, scnt * sizeof(bool));
		for(int i = 0; i < scnt; ++i)
			if(!vis[i])
				dfs(i);
		for(int i = 0; i < scnt; ++i)
		{
			for(int size = query[i].size(), v; fin[i] < size && (v = query[i][fin[i]]) < fir + maxn / 10; ++fin[i])
				if(msk[i].test(v - fir))
				{
					flag = 0;
					break;
				}
			if(!flag)
				break;
		}
		if(!flag)
			break;
	}
	if(!flag)
		puts("NO");
	else
	{
		puts("YES");
		printf("%d\n", m);
		for(int i = 0; i < n; ++i)
			for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
				printf("%d %d\n", i + 1, (*it) + 1);
	}
	return 0;
}
