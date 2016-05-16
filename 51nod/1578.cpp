#include <map>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 1000001;
std::map<int, int> chd[maxn];
int tot, pos, fa[maxn], fa1[maxn];
int size[3], sz[maxn];
LL dmax[3], dmin[3], dcnt[3], dist[maxn], dist1[maxn];
std::vector<int> e[maxn], e1[maxn];
void pfs1(int u)
{
	sz[u] = 0;
	dist[u] = 0;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa[u])
			continue;
		pfs1(v);
		sz[u] += sz[v];
		dist[u] += dist[v] + sz[v];
	}
	++sz[u];
}
void dfs1(int u)
{
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int v = *it;
		if(v == fa[u])
			continue;
		dist[v] += dist[u] - dist[v] - sz[v] + tot - sz[v];
		dfs1(v);
	}
}
void solve(int idx)
{
	pos = 0;
	tot = 1;
	for(int ch = getchar(), num; ch != '\n' && ch != EOF; )
	{
		for( ; !isdigit(ch); ch = getchar());
		for(num = 0; isdigit(ch); ch = getchar())
			num = (num << 3) + (num << 1) + (ch - '0');
		if(num == 8)
			pos = fa[pos];
		else
		{
			if(!chd[pos].count(num))
			{
				chd[pos][num] = tot;
				fa[tot++] = pos;
			}
			pos = chd[pos][num];
		}
	}
	for(int i = 0; i < tot; ++i)
	{
		std::vector<int>().swap(e[i]);
		for(std::map<int, int>::iterator it = chd[i].begin(); it != chd[i].end(); ++it)
			e[i].push_back(it -> second);
		std::map<int, int>().swap(chd[i]);
	}
	dist[0] = 0;
	pfs1(0);
	dfs1(0);
	size[idx] = tot;
	dmax[idx] = dmin[idx] = dcnt[idx] = dist[0];
	for(int i = 1; i < tot; ++i)
	{
		dcnt[idx] += dist[i];
		if(dmax[idx] < dist[i])
			dmax[idx] = dist[i];
		else if(dmin[idx] > dist[i])
			dmin[idx] = dist[i];
	}
	dcnt[idx] >>= 1;
	if(idx == 1)
	{
		memcpy(fa1, fa, tot * sizeof(int));
		memcpy(dist1, dist, tot * sizeof(LL));
		for(int i = 0; i < tot; ++i)
			e1[i].swap(e[i]);
	}
}
int pos1[maxn], pos2[maxn];
LL val1[maxn], val2[maxn];
void pfs2(int u)
{
	val1[u] = dist1[u];
	pos1[u] = u;
	val2[u] = -1;
	pos2[u] = -1;
	for(std::vector<int>::iterator it = e1[u].begin(); it != e1[u].end(); ++it)
	{
		int v = *it;
		if(v == fa1[u])
			continue;
		pfs2(v);
		{
			LL val = val1[v] + size[0];
			if(val1[u] < val)
			{
				val2[u] = val1[u];
				pos2[u] = pos1[u];
				val1[u] = val;
				pos1[u] = v;
			}
			else if(val2[u] < val)
			{
				val2[u] = val;
				pos2[u] = v;
			}
		}
		if(val2[v] != -1)
		{
			LL val = val2[v] + size[0];
			if(val1[u] < val)
			{
				val2[u] = val1[u];
				pos2[u] = pos1[u];
				val1[u] = val;
				pos1[u] = v;
			}
			else if(val2[u] < val)
			{
				val2[u] = val;
				pos2[u] = v;
			}
		}
	}
}
void dfs2(int u)
{
	for(std::vector<int>::iterator it = e1[u].begin(); it != e1[u].end(); ++it)
	{
		int v = *it;
		if(v == fa1[u])
			continue;
		if(pos1[u] != v)
		{
			LL val = val1[u] + size[0];
			if(val1[v] < val)
			{
				val2[v] = val1[v];
				pos2[v] = pos1[v];
				val1[v] = val;
				pos1[v] = u;
			}
			else if(val2[v] < val)
			{
				val2[v] = val;
				pos2[v] = u;
			}
		}
		if(pos2[u] != v)
		{
			LL val = val2[u] + size[0];
			if(val1[v] < val)
			{
				val2[v] = val1[v];
				pos2[v] = pos1[v];
				val1[v] = val;
				pos1[v] = u;
			}
			else if(val2[v] < val)
			{
				val2[v] = val;
				pos2[v] = u;
			}
		}
		dfs2(v);
	}
}
LL check()
{
	pfs2(0);
	dfs2(0);
	LL ret = 0;
	for(int i = 0; i < size[1]; ++i)
		if(ret < size[0] * dist1[i] + size[2] * val1[i])
			ret = size[0] * dist1[i] + size[2] * val1[i];
	return ret;
}
int main()
{
	for(int i = 0; i < 3; ++i)
		solve(i);
	LL tmin = dcnt[0], tmax = dcnt[0];
	printf("%lld %lld\n", tmin, tmax);
	tmin += dcnt[1] + (size[0] + dmin[0]) * size[1];
	tmax += dcnt[1] + (size[0] + dmax[0]) * size[1];
	printf("%lld %lld\n", tmin + size[0] * dmin[1], tmax + size[0] * dmax[1]);
	tmin += dcnt[2] + (2 * size[0] + size[1] + dmin[0]) * size[2] + (size[0] + size[1]) * dmin[2];
	tmax += dcnt[2] + (2 * size[0] + size[1] + dmax[0]) * size[2] + (size[0] + size[1]) * dmax[2];
	printf("%lld %lld\n", tmin + (size[0] + size[2]) * dmin[1], tmax + check());
	return 0;
}
