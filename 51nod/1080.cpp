#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxs = 65, maxm = 1 << 16, maxt = 10;
LL gcd(LL a, LL b)
{
	return b ? gcd(b, a % b) : a;
}
void exgcd(LL a, LL b, LL &x, LL &y)
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
LL mod_add(LL x, LL y, LL p)
{
	LL ret = x + y;
	if(ret >= p)
		ret -= p;
	return ret;
}
LL mod_mul(LL x, LL y, LL p)
{
	LL ret = 0;
	while(y)
	{
		if(y & 1)
			ret = mod_add(ret, x, p);
		x = mod_add(x, x, p);
		y >>= 1;
	}
	return ret;
}
LL mod_pow(LL x, LL k, LL p)
{
	LL ret = 1;
	while(k)
	{
		if(k & 1)
			ret = mod_mul(ret, x, p);
		x = mod_mul(x, x, p);
		k >>= 1;
	}
	return ret;
}
bool miller_rabin(LL n)
{
	if(n == 2)
		return 1;
	if(n < 2 || !(n & 1))
		return 0;
	LL s = 0, r = n - 1;
	for( ; !(r & 1); r >>= 1)
		++s;
	for(int i = 0; i < maxt; ++i)
	{
		LL cur = mod_pow(rand() % (n - 2) + 2, r, n), nxt;
		for(int j = 0; j < s; ++j)
		{
			nxt = mod_mul(cur, cur, n);
			if(nxt == 1 && cur != 1 && cur != n - 1)
				return 0;
			cur = nxt;
		}
		if(cur != 1)
			return 0;
	}
	return 1;
}
LL pollard_rho(LL n)
{
	LL x = (LL)rand() * rand() % n, y = x, c = (LL)rand() * rand() % n, r;
	for(LL i = 1, k = 2; ; ++i)
	{
		if(i == k)
		{
			y = x;
			k <<= 1;
		}
		x = mod_add(mod_mul(x, x, n), c, n);
		r = gcd(abs(y - x), n);
		if(r != 1)
			return r;
	}
}
int cnt;
LL p[maxs];
void decomposition(LL n)
{
	if(miller_rabin(n))
		p[cnt++] = n;
	else
	{
		LL fact;
		while((fact = pollard_rho(n)) == n);
		decomposition(fact);
		decomposition(n / fact);
	}
}
struct Matrix
{
	int r, c;
	LL mod, num[2][2];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {};
		ret.r = r;
		ret.c = t.c;
		ret.mod = mod;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = mod_add(ret.num[i][k], mod_mul(num[i][j], t.num[j][k], mod), mod);
		return ret;
	}
	Matrix pow(LL k)
	{
		Matrix ret = {}, tmp = *this;
		ret.r = ret.c = r;
		ret.mod = mod;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
};
pair<LL, LL> gao(LL p)
{
	LL a, m, sp = (LL)sqrt(p);
	do
	{
		a = rand() % sp;
		m = a * a + 1;
	} while(mod_pow(m, p - 1 >> 1, p) == 1);
	LL x = p, y = (Matrix){2, 2, p, a, 1, m, a}.pow(p + 1 >> 1).num[0][0], r = x % y;
	for(r = x % y; r >= sp; x = y, y = r, r = x % y);
	x = r;
	y = (LL)sqrt(p - r * r);
	return x <= y ? make_pair(x, y) : make_pair(y, x);
}
int tot, sz[2];
pair<LL, LL> fact[maxs], ans[2][maxm];
int main()
{
	LL n;
	scanf("%lld", &n);
	if(n == 1)
	{
		puts("0 1");
		return 0;
	}
	decomposition(n);
	sort(p, p + cnt);
	for(int i = 0, o; i <= cnt; ++i)
		if(i && p[i - 1] == p[i])
			++o;
		else if((p[i - 1] & 3) == 3 && (o & 1))
		{
			puts("No Solution");
			return 0;
		}
		else
			o = 1;
	for(int i = 0; i < cnt; ++i)
		if(p[i] == 2)
			fact[tot++] = make_pair(1, 1);
		else if((p[i] & 3) == 3)
			fact[tot++] = make_pair(0, p[i++]);
		else
			fact[tot++] = gao(p[i]);
	int pre = 1, cur = 0;
	ans[cur][sz[cur]++] = fact[0];
	for(int i = 1; i < tot; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		sz[cur] = 0;
		for(int j = 0; j < sz[pre]; ++j)
		{
			LL a = ans[pre][j].first, b = ans[pre][j].second, c = fact[i].first, d = fact[i].second;
			{
				LL e = a * c + b * d, f = abs(a * d - b * c);
				if(e <= f)
					ans[cur][sz[cur]++] = make_pair(e, f);
				else
					ans[cur][sz[cur]++] = make_pair(f, e);
			}
			{
				LL e = abs(a * c - b * d), f = a * d + b * c;
				if(e <= f)
					ans[cur][sz[cur]++] = make_pair(e, f);
				else
					ans[cur][sz[cur]++] = make_pair(f, e);
			}
		}
		sort(ans[cur], ans[cur] + sz[cur]);
		sz[cur] = unique(ans[cur], ans[cur] + sz[cur]) - ans[cur];
	}
	for(int i = 0; i < sz[cur]; ++i)
		printf("%lld %lld\n", ans[cur][i].first, ans[cur][i].second);
	return 0;
}
