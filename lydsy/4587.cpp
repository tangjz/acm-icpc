#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxp = 46341, maxc = 11, maxk = 11, maxe = 51;
void exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int mod_inv(int x, int p)
{
	int s, t;
	exgcd(x, p, s, t);
	return s < 0 ? s + p : s;
}
int tot, prime[maxp], fir[maxp], mod, cnt, fact[maxc], Exp[maxc], Coeff, Lim[maxc], Pw[maxc][maxe];
inline void mod_dec(int &x, int y, int c = 1)
{
	while(c--)
		if((x -= y) < 0)
			x += mod;
}
void init()
{
	Coeff = 1;
	for(int i = 0; i < cnt; ++i)
	{
		Exp[i] = Lim[i] = 0;
		Pw[i][0] = 1;
	}
}
void update(int val, int flag)
{
	for(int i = 0; i < cnt; ++i)
		for( ; val % fact[i] == 0; Exp[i] += flag, val /= fact[i]);
	Coeff = (LL)Coeff * (flag == 1 ? val : mod_inv(val, mod)) % mod;
}
int query()
{
	int ret = Coeff;
	for(int j = 0; j < cnt && ret; ++j)
	{
		if(!Exp[j])
			continue;
		for( ; Lim[j] < Exp[j]; ++Lim[j])
			Pw[j][Lim[j] + 1] = (LL)Pw[j][Lim[j]] * fact[j] % mod;
		ret = (LL)ret * Pw[j][Exp[j]] % mod;
	}
	return ret;
}
int calc_1(int n, int m)
{
	if(n > m)
		std::swap(n, m);
	if(n < 0)
		return 0;
	else if(!n)
		return 1;
	int ret = 0;
	init();
	for(int i = 1; i <= n; ++i)
	{
		update(m + i, 1);
		update(i, -1);
	}
	for(int i = 0; i <= n; ++i)
	{
		mod_dec(ret, mod - query());
		if(i == n)
			break;
		update(n - i, 1);
		update(m - i, 1);
		update(n + m - i, -1);
		update(i + 1, -1);
	}
	return ret;
}
int calc_2(int n, int m)
{
	if(n > m)
		std::swap(n, m);
	if(n < 0)
		return 0;
	else if(!n)
		return 1;
	int ret = 0;
	--n;
	--m;
	init();
	for(int i = 1; i <= n; ++i)
	{
		update(m + i, 1);
		update(i, -1);
	}
	update(n + m + 1, 1);
	for(int i = 0; i <= n; ++i)
	{
		update(n + 1, -1);
		mod_dec(ret, mod - query(), 2);
		update(n + 1, 1);
		update(m + 1, -1);
		mod_dec(ret, mod - query(), 2);
		update(m + 1, 1);
		update(n + m + 1 - i, -1);
		mod_dec(ret, query());
		if(i == n)
			break;
		update(n - i, 1);
		update(m - i, 1);
		update(i + 1, -1);
	}
	return ret;
}
int t, n, m, k, f[maxk], ans;
std::pair<int, int> lim[maxk];
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!fir[i])
			prime[tot++] = fir[i] = i;
		for(int j = 0, k; (k = i * prime[j]) < maxp; ++j)
		{
			fir[k] = prime[j];
			if(fir[i] == prime[j])
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &n, &m, &k, &mod);
		int tmp = mod;
		cnt = 0;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
				for(fact[cnt++] = prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
		if(tmp > 1)
			fact[cnt++] = tmp;
		for(int i = 0; i < k; ++i)
			scanf("%d%d", &lim[i].first, &lim[i].second);
		std::sort(lim, lim + k);
		k = std::unique(lim, lim + k) - lim;
		for(int i = 0; i < k; ++i)
		{
			int &ai = lim[i].first, &bi = lim[i].second;
			if(ai < n && bi < m)
			{
				f[i] = calc_1(ai, bi);
				for(int j = 0; j < i; ++j)
				{
					int &aj = lim[j].first, &bj = lim[j].second;
					int coeff = calc_1(ai - aj, bi - bj);
					if(coeff)
						f[i] = (f[i] - (LL)coeff * f[j]) % mod;
				}
			}
			else
			{
				f[i] = calc_1(ai - 1, bi - 1);
				if(ai < n)
					mod_dec(f[i], mod - calc_1(ai, bi - 1));
				if(bi < m)
					mod_dec(f[i], mod - calc_1(ai - 1, bi));
				for(int j = 0; j < i; ++j)
				{
					int &aj = lim[j].first, &bj = lim[j].second;
					int coeff = calc_1(ai - 1 - aj, bi - 1 - bj);
					if(ai < n)
						mod_dec(coeff, mod - calc_1(ai - aj, bi - 1 - bj));
					if(bi < m)
						mod_dec(coeff, mod - calc_1(ai - 1 - aj, bi - bj));
					if(coeff)
						f[i] = (f[i] - (LL)coeff * f[j]) % mod;
				}
			}
		}
		ans = calc_2(n, m);
		for(int i = 0; i < k; ++i)
		{
			int coeff = calc_2(n - lim[i].first, m - lim[i].second);
			if(coeff)
				ans = (ans - (LL)coeff * f[i]) % mod;
		}
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
