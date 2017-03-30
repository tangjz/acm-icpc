#include <cstdio>
#include <vector>
#include <cstring> 
#include <algorithm>
using namespace std;
const int maxn = 200010, mod = 1000000007;
int n, f[maxn], g[maxn];
vector<int> e[maxn];
bool vis[maxn], isleaf[maxn];
int pow(int x, unsigned int k, int mod)
{
	int ret = 1;
	x %= mod;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int inv(int x)
{
	return pow(x, mod - 2, mod);
}
void pfs(int u)
{
	vis[u] = 1;
	f[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		int &v = *it;
		if(vis[v])
			continue;
		pfs(v);
		f[u] = (long long)f[u] * (f[v] + 1) % mod;
	}
}
void dfs(int u)
{
	vis[u] = 1;
	++g[u];
	if(!f[u])
	{
		int cnt = 0, pos;
		for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int &v = *it;
			if(vis[v])
				continue;
			if(f[v] + 1 == mod)
			{
				++cnt;
				pos = v;
			}
		}
		if(cnt == 1)
		{
			int res = 1;
			for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int &v = *it;
				if(vis[v] || v == pos)
					continue;
				res = (long long)res * (f[v] + 1) % mod;
			}
			g[pos] = (long long)g[u] * res % mod;
		}
		for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int &v = *it;
			if(vis[v])
				continue;
			dfs(v);
		}
	}
	else
		for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int &v = *it;
			if(vis[v])
				continue;
			g[v] = (long long)g[u] * f[u] % mod * inv(f[v] + 1) % mod;
			dfs(v);
		}
}
int main()
{
	scanf("%d", &n);
	for(int i = 2, x; i <= n; ++i)
	{
		scanf("%d", &x);
		e[i].push_back(x);
		e[x].push_back(i);
	}
	pfs(1);
	memset(vis, 0, sizeof vis);
	dfs(1);
	for(int i = 1; i <= n; ++i)
		printf("%d ", (long long)f[i] * g[i] % mod);
	return 0;
}
