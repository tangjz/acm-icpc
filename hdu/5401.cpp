#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxm = 61, mod = 1000000007;
map<pair<int, LL>, int> sum;
map<pair<int, pair<LL, LL> >, int> dist;
int m, a[maxm], b[maxm], l[maxm], ans[maxm];
LL c[maxm], d[maxm], sz[maxm];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int Dist(int n, LL u, LL v)
{
	if(!n || u == v)
		return 0;
	if(u > v)
		swap(u, v);
	if(dist.count(make_pair(n, make_pair(u, v))))
		return dist[make_pair(n, make_pair(u, v))];
	int ret = 0;
	if(v < sz[a[n]])
		ret = Dist(a[n], u, v);
	else if(u >= sz[a[n]])
		ret = Dist(b[n], u - sz[a[n]], v - sz[a[n]]);
	else
	{
		inc(ret, Dist(a[n], c[n], u));
		inc(ret, Dist(b[n], d[n], v - sz[a[n]]));
		inc(ret, l[n]);
	}
	return dist[make_pair(n, make_pair(u, v))] = ret;
}
int Sum(int n, LL u)
{
	if(!n)
		return 0;
	if(sum.count(make_pair(n, u)))
		return sum[make_pair(n, u)];
	int ret = 0;
	if(u < sz[a[n]])
	{
		inc(ret, Sum(a[n], u));
		inc(ret, Sum(b[n], d[n]));
		inc(ret, (sz[b[n]] % mod) * Dist(n, sz[a[n]] + d[n], u) % mod);
	}
	else
	{
		inc(ret, Sum(b[n], u - sz[a[n]]));
		inc(ret, Sum(a[n], c[n]));
		inc(ret, (sz[a[n]] % mod) * Dist(n, c[n], u) % mod);
	}
	return sum[make_pair(n, u)] = ret;
}
int Ans(int n)
{
	if(ans[n] != -1)
		return ans[n];
	int ret = 0;
	inc(ret, Ans(a[n]));
	inc(ret, Ans(b[n]));
	inc(ret, (sz[a[n]] % mod) * (sz[b[n]] % mod) % mod * l[n] % mod);
	inc(ret, (sz[b[n]] % mod) * Sum(a[n], c[n]) % mod);
	inc(ret, (sz[a[n]] % mod) * Sum(b[n], d[n]) % mod);
	return ans[n] = ret;
}
int main()
{
	while(scanf("%d", &m) == 1)
	{
		memset(ans, -1, sizeof ans);
		dist.clear();
		sum.clear();
		sz[0] = 1;
		ans[0] = 0;
		for(int i = 1; i <= m; ++i)
		{
			scanf("%d%d%lld%lld%d", a + i, b + i, c + i, d + i, l + i);
			sz[i] = sz[a[i]] + sz[b[i]];
		}
		for(int i = 1; i <= m; ++i)
			printf("%d\n", Ans(i));
	}
	return 0;
}
