#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int long long mod1 = 880788066951082291LL, mod2 = 1051263176683549831LL;
typedef pair<long long, int> Edge;
int n, m, s, t, eu[maxn], ev[maxn], ew[maxn];
long long dis1[maxn], dis2[maxn];
vector<Edge> e1[maxn], e2[maxn];
bool vis[maxn];
priority_queue<Edge, vector<Edge>, greater<Edge> > Q;
struct Hash
{
	long long a, b;
	bool operator == (const Hash &x) const
	{
		return a == x.a && b == x.b;
	}
	Hash operator + (const Hash &x) const
	{
		Hash tmp = *this;
		tmp.a += x.a;
		if(tmp.a >= mod1)
			tmp.a -= mod1;
		tmp.b += x.b;
		if(tmp.b >= mod2)
			tmp.b -= mod2;
		return tmp;
	}
	Hash operator * (const Hash &x) const
	{
		Hash ret = {}, tmp = *this, mul = x;
		while(mul.a || mul.b)
		{
			if(mul.a & 1)
			{
				ret.a += tmp.a;
				if(ret.a >= mod1)
					ret.a -= mod1;
			}
			if(mul.b & 1)
			{
				ret.b += tmp.b;
				if(ret.b >= mod2)
					ret.b -= mod2;
			}
			tmp = tmp + tmp;
			mul.a >>= 1;
			mul.b >>= 1;
		}
		return ret;
	}
} path1[maxn], path2[maxn];
int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 0; i < m; ++i)
	{
		scanf("%d%d%d", eu + i, ev + i, ew + i);
		e1[eu[i]].push_back(make_pair(ew[i], ev[i]));
		e2[ev[i]].push_back(make_pair(ew[i], eu[i]));
	}
	memset(dis1, 0x3f, sizeof dis1);
	dis1[s] = 0;
	path1[s] = (Hash){1, 1};
	Q.push(make_pair(dis1[s], s));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(vector<Edge>::iterator it = e1[u].begin(); it != e1[u].end(); ++it)
		{
			int &v = it -> second;
			long long &w = it -> first;
			if(dis1[v] > dis1[u] + w)
			{
				dis1[v] = dis1[u] + w;
				path1[v] = path1[u];
				Q.push(make_pair(dis1[v], v));
			}
			else if(dis1[v] == dis1[u] + w)
				path1[v] = path1[u] + path1[v];
		}
	}
	memset(vis, 0, sizeof vis);
	memset(dis2, 0x3f, sizeof dis2);
	dis2[t] = 0;
	path2[t] = (Hash){1, 1};
	Q.push(make_pair(dis2[t], t));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(vector<Edge>::iterator it = e2[u].begin(); it != e2[u].end(); ++it)
		{
			int &v = it -> second;
			long long &w = it -> first;
			if(dis2[v] > dis2[u] + w)
			{
				dis2[v] = dis2[u] + w;
				path2[v] = path2[u];
				Q.push(make_pair(dis2[v], v));
			}
			else if(dis2[v] == dis2[u] + w)
				path2[v] = path2[u] + path2[v];
		}
	}
	for(int i = 0; i < m; ++i)
		if(dis1[eu[i]] + ew[i] + dis2[ev[i]] == dis1[t] && path1[eu[i]] * path2[ev[i]] == path1[t])
			puts("YES");
		else if(ew[i] > 1 && dis1[eu[i]] + dis2[ev[i]] + 1 < dis1[t])
				printf("CAN %I64d\n", ew[i] - dis1[t] + dis1[eu[i]] + dis2[ev[i]] + 1);
		else
			puts("NO");
	return 0;
}
