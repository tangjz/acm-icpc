#include <map>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 31623, maxs = 10;
int mod_pow(int x, int k, int p)
{
	int ret = 1; // p > 1
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
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
	int ret, tmp;
	exgcd(x, p, ret, tmp);
	return ret < 0 ? ret + p : ret;
}
std::map<int, int> Hash;
int bsgs(int pp, int x, int y) // x^k = y (mod pp)
{
	int sz = (int)ceil(sqrt(pp)), lim = (pp - 1) / sz + 1;
	std::map<int, int>().swap(Hash);
	for(int i = 0, j = 1; i < sz; ++i, j = (LL)j * x % pp)
		if(!Hash.count(j))
			Hash[j] = i;
	int inver = mod_inv(mod_pow(x, sz, pp), pp);
	for(int i = 0, j = y; i < lim; ++i, j = (LL)j * inver % pp)
		if(Hash.count(j))
			return i * sz + Hash[j];
	return -1;
}
int tot, prime[maxn];
bool vis[maxn];
int prim_root(int mod)
{
	int tmp = mod - 1, c = 0;
	static int p[maxs];
	for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
	{
		if(tmp % prime[i])
			continue;
		for(tmp /= prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
		p[c++] = prime[i];
	}
	if(tmp > 1)
		p[c++] = tmp;
	for(int g = 2; ; ++g)
	{
		bool flag = mod_pow(g, mod - 1, mod) == 1;
		for(int i = 0; i < c && flag; ++i)
			flag &= mod_pow(g, (mod - 1) / p[i], mod) != 1;
		if(flag)
			return g;
	}
}
int t, a, b, m, c, p[maxs], e[maxs];
int M, sz, cur, out[maxn], tmp;
void solve(int o, int k, int y) // x^k = y (mod p^e)
{
	int mod = 1, tsz = 0;
	static int seq[maxn];
	for(int i = 0; i < e[o]; ++i)
		mod *= p[o];
	int r = std::__gcd(mod, y %= mod), ret = 1, sei = M / mod * (LL)mod_inv(M / mod, mod) % M;
	if(!y)
	{
		for(int i = 0; i < (e[o] - 1) / k + 1; ++i)
			ret *= p[o];
		for(int i = ret; i <= mod; i += ret)
			for(int j = 0; j < sz; ++j)
				seq[tsz++] = (out[j] + (LL)sei * i) % M;
	}
	else
	{
		if(r > 1)
		{
			int cnt = 0;
			for( ; y % p[o] == 0; ++cnt, y /= p[o], mod /= p[o]);
			if(cnt % k)
			{
				sz = 0;
				return;
			}
			for(int i = cnt / k; i < cnt; ++i)
				ret *= p[o];
		}
		int g = prim_root(p[o]), id = bsgs(mod, g, y), phi = mod - mod / p[o];
		r = std::__gcd(k, phi);
		if(id != -1 && id % r == 0)
		{
			k /= r;
			phi /= r;
			id /= r;
			int inver = (LL)mod_inv(k, phi) * id % phi, delta = mod_pow(g, phi, mod);
			for(int i = 0, val = mod_pow(g, inver, mod); i < r; ++i, val = (LL)val * delta % mod)
				for(int j = 0, v = val; j < ret; ++j, v += mod)
					for(int k = 0; k < sz; ++k)
						seq[tsz++] = (out[k] + (LL)sei * v) % M;
		}
	}
	sz = tsz;
	memcpy(out, seq, tsz * sizeof(int));
}
void solve2(int k, int y) // x^k = y (mod 2^e)
{
	int mod = 1, tsz = 0, L = 0, R = 0;
	static int seq[maxn], que[maxn];
	que[R++] = 0;
	for(int i = 1; i <= e[0]; ++i, mod <<= 1)
		for(int lim = R; L != lim; L = L + 1 < maxn ? L + 1 : 0)
		{
			if(mod_pow(que[L], k, mod << 1) == (y & ((mod << 1) - 1)))
			{
				que[R++] = que[L];
				if(R == maxn)
					R = 0;
			}
			if(mod_pow(que[L] + mod, k, mod << 1) == (y & ((mod << 1) - 1)))
			{
				que[R++] = que[L] + mod;
				if(R == maxn)
					R = 0;
			}
		}
	int sei = M / mod * (LL)mod_inv(M / mod, mod) % M;
	for( ; L != R; L = L + 1 < maxn ? L + 1 : 0)
		for(int i = 0; i < sz; ++i)
			seq[tsz++] = (out[i] + (LL)sei * que[L]) % M;
	sz = tsz;
	memcpy(out, seq, tsz * sizeof(int));
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && i * prime[j] < maxn; ++i)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &a, &m, &b);
		M = m;
		c = 0;
		for(int i = 0; i < tot && prime[i] * prime[i] <= m; ++i)
		{
			if(m % prime[i])
				continue;
			for(e[c] = 1, m /= prime[i]; m % prime[i] == 0; ++e[c], m /= prime[i]);
			p[c++] = prime[i];
		}
		if(m > 1)
		{
			p[c] = m;
			e[c++] = 1;
		}
		sz = 1;
		out[0] = 0;
		if(p[0] == 2)
			solve2(a, b);
		for(int i = p[0] == 2; i < c && sz; ++i)
			solve(i, a, b);
		if(!sz)
		{
			puts("No Solution");
			continue;
		}
		std::sort(out, out + sz);
		for(int i = 0; i < sz; ++i)
			printf("%d%c", out[i], " \n"[i == sz - 1]);
	}
	return 0;
}
