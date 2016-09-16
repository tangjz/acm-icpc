#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxd = 2, maxs = 11, seed = 985661441, mod = 1000000009;
int tot;
std::map<std::string, int> Table;
char Name[2][maxn][maxs], (* name)[maxs] = Name[0], (* pname)[maxs] = Name[1];
int n, sz[maxn], psz[maxn], cnt, rt[maxd], rtH[maxd], pcnt, prt[maxd], prtH[maxd], match[maxn];
std::vector<int> e[maxn];
std::vector<std::pair<int, int> > Hash[maxd][maxn], pHash[maxd][maxn];
inline int getID(char s[maxs])
{
	if(Table.count(s))
		return Table[s];
	strcpy(name[tot], s);
	return Table[s] = tot++;
}
std::vector<std::pair<int, int> > *HH, *pHH;
bool vis[maxn];
void pfs(int u)
{
	int mx = 0;
	vis[u] = 1;
	sz[u] = 1;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(vis[*it])
			continue;
		pfs(*it);
		if(mx < sz[*it])
			mx = sz[*it];
		sz[u] += sz[*it];
	}
	if(mx < n - sz[u])
		mx = n - sz[u];
	if(!cnt || mx < rtH[0])
	{
		rt[0] = u;
		rtH[0] = mx;
		cnt = 1;
	}
	else if(cnt < 2 && rtH[0] == mx)
		rt[cnt++] = u;
}
bool cmp(const std::pair<int, int> &x, const std::pair<int, int> &y)
{
	return x.first < y.first;
}
int dfs(int u)
{
	vis[u] = 1;
	sz[u] = 1;
	std::vector<std::pair<int, int> >().swap(HH[u]);
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(vis[*it])
			continue;
		HH[u].push_back(std::make_pair(dfs(*it), *it));
		sz[u] += sz[*it];
	}
	int ret = 1;
	std::sort(HH[u].begin(), HH[u].end(), cmp);
	for(std::vector<std::pair<int, int> >::iterator it = HH[u].begin(); it != HH[u].end(); ++it)
		ret = ((LL)ret * seed + (it -> first)) % mod;
	return ret;
}
void treeInit()
{
	tot = cnt = 0;
	std::map<std::string, int>().swap(Table);
	for(int i = 0; i < n; ++i)
		std::vector<int>().swap(e[i]);
	static char str[maxs];
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%s", str);
		u = getID(str);
		scanf("%s", str);
		v = getID(str);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	memset(vis, 0, n * sizeof(bool));
	pfs(0); // find center
	for(int i = 0; i < cnt; ++i)
	{
		memset(vis, 0, n * sizeof(bool));
		HH = Hash[i];
		rtH[i] = dfs(rt[i]); // calc hash
	}
}
void treeSwap()
{
	std::swap(name, pname);
	for(int i = 0; i < n; ++i)
		std::swap(sz[i], psz[i]);
	for(int i = 0; i < cnt; ++i)
	{
		std::swap(rt[i], prt[i]);
		std::swap(rtH[i], prtH[i]);
		for(int j = 0; j < n; ++j)
			Hash[i][j].swap(pHash[i][j]);
	}
	std::swap(cnt, pcnt);
}
bool check(int u, int pu)
{
	if(sz[u] != psz[pu] || HH[u].size() != pHH[pu].size())
		return 0;
	for(int i = 0, size = (int)HH[u].size(); i < size; ++i)
	{
		bool flag = 0;
		for(int j = i; j < size && HH[u][i].first == pHH[pu][j].first; ++j)
			if(check(HH[u][i].second, pHH[pu][j].second))
			{
				std::swap(pHH[pu][i], pHH[pu][j]);
				flag = 1;
				break;
			}
		if(!flag)
			return 0;
	}
	match[pu] = u;
	return 1;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		treeInit();
		treeSwap();
		treeInit();
		bool flag = 0;
		for(int i = 0; i < cnt && !flag; ++i)
		{
			HH = Hash[i];
			for(int j = 0; j < pcnt && !flag; ++j)
			{
				if(rtH[i] != prtH[j])
					continue;
				pHH = pHash[j];
				flag |= check(rt[i], prt[j]);
			}
		}
		for(int i = 0; i < n; ++i)
			printf("%s %s\n", pname[i], name[match[i]]);
	}
	return 0;
}
