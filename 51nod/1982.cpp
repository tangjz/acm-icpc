#include <set>
#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 100001, maxv = 100005, maxp = 9593;
int tot, pr[maxp], d[maxv], n, mx, e[maxp], cnt, num[maxv];
LL ctr, c[maxv], pw[maxv];
std::multiset<LL> sp;
int main()
{
	memset(d, -1, sizeof d);
	for(int i = 2; i < maxv; ++i)
	{
		if(d[i] == -1)
		{
			d[i] = tot;
			pr[tot++] = i;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxv; ++j)
		{
			d[k] = j;
			if(d[i] == j)
				break;
		}
	}
	scanf("%d", &n);
	while(n--)
	{
		int x;
		scanf("%d", &x);
		++c[x];
		if(mx < x)
			mx = x;
	}
	for(int i = mx; i > 2; --i)
		c[i - 1] += c[i];
	for(int i = mx; i > 2; --i)
	{
		int pp = pr[d[i]];
		if(i == pp)
			continue;
		c[pp] += c[i];
		c[i / pp] += c[i];
	}
	for(++mx; pr[d[mx]] < mx; ++mx);
	for(int i = 0, m = d[mx--]; i < m; ++i)
	{
		c[i] = c[pr[i]];
		for(int j = mx / pr[i]; j; j /= pr[i])
			e[i] += j;
		sp.insert(c[i] / e[i]);
	}
	for( ; mx > 1; --mx)
	{
		LL ex = *sp.begin();
		if(ctr < ex)
		{
			num[cnt] = mx;
			pw[cnt++] = ex - ctr;
			ctr = ex;
		}
		for(int val = mx; val > 1; )
		{
			int id = d[val], pp = pr[id], ee;
			for(ee = 1, val /= pp; d[val] == id; ++ee, val /= pp);
			sp.erase(sp.find(c[id] / e[id]));
			c[id] -= ee * ctr;
			e[id] -= ee;
			if(e[id])
				sp.insert(c[id] / e[id]);
		}
	}
	printf("%d\n", cnt);
	for(int i = 0; i < cnt; ++i)
		printf("%d %lld\n", num[i], pw[i]);
	return 0;
}
