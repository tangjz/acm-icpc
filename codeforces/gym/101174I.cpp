#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 203, maxm = 501, mod = 13;
int n, m, tot, S, T, inv[mod], f[maxm][maxn], dis[maxn];
map<pair<int, int>, int> sp;
inline int getID(int u, int v)
{
	if(u > v)
		swap(u, v);
	pair<int, int> state = make_pair(u, v);
	return sp.count(state) ? sp[state] : (sp[state] = tot++);
}
vector<pair<int, int> > e[maxn];
bool vis[maxn];
int main()
{
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	scanf("%d%d%d%d", &n, &S, &T, &m);
	for(int i = 0; i < m; ++i)
	{
		int c, p = -1;
		scanf("%d%d", f[i] + (maxn - 1), &c);
		while(c--)
		{
			int x;
			scanf("%d", &x);
			if(p != -1)
				++f[i][getID(p, x)];
			p = x;
		}
	}
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < tot; ++j)
			f[i][j] %= mod;
		f[i][tot] = f[i][maxn - 1] % mod;
	}
	for(int i = 0; i < tot; ++i)
	{
		int k = -1;
		for(int j = i; j < m && k == -1; ++j)
			if(f[j][i])
				k = j;
		//assert(k != -1);
		if(k != i)
			for(int j = i; j <= tot; ++j)
				swap(f[i][j], f[k][j]);
		int ivs = inv[f[i][i]];
		for(int j = i; j <= tot; ++j)
			f[i][j] = f[i][j] * ivs % mod;
		for(int j = 0; j < m; ++j)
		{
			if(i == j || !f[j][i])
				continue;
			int coeff = mod - f[j][i];
			for(int k = i; k <= tot; ++k)
				f[j][k] = (f[j][k] + coeff * f[i][k]) % mod;
		}
	}
	for(map<pair<int, int>, int>::iterator it = sp.begin(); it != sp.end(); ++it)
	{
		int u = (it -> first).first, v = (it -> first).second, id = it -> second;
		e[u].push_back(make_pair(v, f[id][tot]));
		e[v].push_back(make_pair(u, f[id][tot]));
	}
	memset(dis + 1, 0x3f, n * sizeof(int));
	dis[S] = 0;
	for(int i = 1; i < n; ++i)
	{
		int j = -1;
		for(int k = 1; k <= n; ++k)
			if(!vis[k] && (j == -1 || dis[k] < dis[j]))
				j = k;
		if(j == -1 || j == T)
			break;
		vis[j] = 1;
		for(vector<pair<int, int> >::iterator it = e[j].begin(); it != e[j].end(); ++it)
		{
			int k = it -> first, w = dis[j] + (it -> second);
			if(w < dis[k])
				dis[k] = w;
		}
	}
	printf("%d\n", dis[T]);
	return 0;
}
