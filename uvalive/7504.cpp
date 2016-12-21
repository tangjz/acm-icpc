#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 6721, maxm = 1000001, maxe = 13, maxk = 10001, mod = 1000000007;
int t, n, r, c, tot, prime[maxm], d[maxm], perm[maxk], ctr[maxn];
LL sei[maxn];
struct Factor
{
	int cnt, p[maxe], e[maxe], tot;
	pair<LL, LL> fact[maxn];
	void generate();
	Factor operator + (const Factor &t) const
	{
		Factor ret = {0};
		for(int i = 0, j = 0; i < cnt || j < t.cnt; ++ret.cnt)
			if(i < cnt && j < t.cnt && p[i] == t.p[j])
			{
				ret.p[ret.cnt] = p[i];
				ret.e[ret.cnt] = e[i++] + t.e[j++];
			}
			else if(j >= t.cnt || (i < cnt && p[i] < t.p[j]))
			{
				ret.p[ret.cnt] = p[i];
				ret.e[ret.cnt] = e[i++];
			}
			else
			{
				ret.p[ret.cnt] = t.p[j];
				ret.e[ret.cnt] = t.e[j++];
			}
		ret.generate();
		return ret;
	}
	void init(int n)
	{
		for(cnt = 0; d[n] > 1; ++cnt)
			for(p[cnt] = d[n], e[cnt] = 0; p[cnt] == d[n]; ++e[cnt], n /= d[n]);
		generate();
	}
	int getID(LL x)
	{
		int idx = lower_bound(fact, fact + tot, make_pair(x, 0LL)) - fact;
		return fact[idx].first == x ? idx : -1;
	}
} fr, fc, frc, *cur;
void dfs(int dep, LL val, LL phi)
{
	if(dep == (cur -> cnt))
	{
		cur -> fact[cur -> tot] = make_pair(val, phi);
		++(cur -> tot);
		return;
	}
	dfs(dep + 1, val, phi);
	for(int i = 1; i <= (cur -> e[dep]); ++i)
		dfs(dep + 1, val *= cur -> p[dep], phi *= cur -> p[dep] - (i == 1));
}
void Factor::generate()
{
	cur = this;
	tot = 0;
	dfs(0, 1LL, 1LL);
	sort(fact, fact + tot);
}
int mod_pow(int x, LL k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
LL lcm(int x, int y)
{
	return x / __gcd(x, y) * (LL)y;
}
int main()
{
	d[1] = 1;
	for(int i = 2; i < maxm; ++i)
	{
		if(!d[i])
			prime[tot++] = d[i] = i;
		for(int j = 0, k = (maxm - 1) / i; prime[j] <= k; ++j)
		{
			d[i * prime[j]] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &r, &c);
		for(int i = 0; i < n; ++i)
			scanf("%d", perm + i);
		fr.init(r);
		fc.init(c);
		frc = fr + fc;
		memset(ctr, 0, frc.tot * sizeof(LL));
		for(int i = 0; i < n; ++i)
		{
			if(perm[i] == -1)
				continue;
			int cnt = 1, j, k;
			for(j = i; perm[j] != i; k = j, j = perm[j], perm[k] = -1, ++cnt);
			perm[j] = -1;
			j = frc.getID(cnt);
			if(j >= 0)
				ctr[j] += cnt;
		}
		memset(sei, 0, frc.tot * sizeof(LL));
		for(int i = 0; i < fr.tot; ++i)
			for(int j = 0; j < fc.tot; ++j)
				sei[frc.getID(lcm(fr.fact[i].first, fc.fact[j].first))] += fr.fact[i].second * fc.fact[j].second;
		int ans = 0;
		for(int i = 0; i < frc.tot; ++i)
		{
			if(!sei[i])
				continue;
			int sum = 0;
			for(int j = 0; j <= i && frc.fact[j].first <= n; ++j)
				if(frc.fact[i].first % frc.fact[j].first == 0)
					sum += ctr[j];
			if(sum > 0)
				ans = (ans + sei[i] % mod * mod_pow(sum, frc.fact[frc.tot - 1].first / frc.fact[i].first)) % mod;
		}
		ans = (LL)ans * mod_inv(frc.fact[frc.tot - 1].first % mod) % mod;
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
