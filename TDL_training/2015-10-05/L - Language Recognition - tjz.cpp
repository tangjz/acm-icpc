#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxs = 31, maxn = 5001, maxd = 26, seed1 = 901013, seed2 = 17, mod = 99999983, s1 = 1879997, s2 = 4381013;
int n, tot, ord[maxn * maxs];
char str[maxs];
struct Trie
{
	int nxt[maxd];
	bool val;
} e[maxn * maxs];
struct Hash
{
	int val, sz, dep;
	bool operator == (const Hash &x) const
	{
		return val == x.val && sz == x.sz && dep == x.dep;
	}
	bool operator < (const Hash &x) const
	{
		if(val != x.val)
			return val < x.val;
		if(sz != x.sz)
			return sz < x.sz;
		return dep < x.dep;
	}
} p[maxn * maxs];
void insert()
{
	int o = 0;
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
	{
		str[i] -= 'a';
		if(!e[o].nxt[str[i]])
		{
			memset(&e[tot], 0, sizeof e[0]);
			e[o].nxt[str[i]] = tot++;
		}
		o = e[o].nxt[str[i]];
	}
	e[o].val = 1;
}
void dfs(int o)
{
	p[o] = (Hash){0, 1, 0};
	for(int i = 0; i < maxd; ++i)
		if(e[o].nxt[i])
		{
			dfs(e[o].nxt[i]);
			p[o].val = ((LL)p[o].val * seed1 + (LL)p[e[o].nxt[i]].val * seed2) % mod;
			p[o].sz += p[e[o].nxt[i]].sz;
			p[o].dep = max(p[o].dep, p[e[o].nxt[i]].dep + 1);
		}
		else
			p[o].val = (LL)p[o].val * seed1 % mod;
	p[o].val ^= e[o].val ? s1 : s2;
}
bool cmp(const int &x, const int &y)
{
	return p[x] < p[y];
}
bool equiv(const int &x, const int &y)
{
	if(!(p[x] == p[y]))
		return 0;
	for(int i = 0; i < maxd; ++i)
	{
		if(e[x].nxt[i] && e[y].nxt[i])
		{
			if(!equiv(e[x].nxt[i], e[y].nxt[i]))
				return 0;
		}
		else if(e[x].nxt[i] != e[y].nxt[i])
			return 0;
	}
	return 1;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		tot = 1;
		memset(&e[0], 0, sizeof e[0]);
		for(int i = 0; i < n; ++i)
			insert();
		dfs(0);
		for(int i = 0; i < tot; ++i)
			ord[i] = i;
		sort(ord, ord + tot, cmp);
		int ans = tot;
		for(int i = 1; i < tot; ++i)
			if(equiv(ord[i - 1], ord[i]))
				--ans;
		printf("%d\n", ans);
	}
	return 0;
}
