#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int maxn = 1000001, maxt = 10, maxs = 5;
typedef long long LL;
inline LL mod_add(LL x, LL y, LL p)
{
	return x + y >= p ? x + y - p : x + y;
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
int tot, prime[maxn / 12], cnt, c[maxs];
bool vis[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	for(LL m, n; scanf("%lld%lld", &m, &n) == 2; )
		if(n % m)
			puts("Wario_wins!\n");
		else
		{
			n /= m;
			cnt = 0;
			for(int i = 0; i < tot && (LL)prime[i] * prime[i] * prime[i] <= n; ++i)
				if(n % prime[i] == 0)
				{
					for(c[cnt] = 0; n % prime[i] == 0; n /= prime[i], ++c[cnt]);
					if(++cnt > 3)
						break;
				}
			if(cnt > 3)
				puts("Mario_wins!\n");
			else if(!cnt)
				puts("Wario_wins!\n");
			else
			{
				if(miller_rabin(n))
					c[cnt++] = 1;
				else if(n > 1)
				{
					m = (LL)sqrt(n);
					if(m * m == n)
						c[cnt++] = 2;
					else
					{
						c[cnt++] = 1;
						c[cnt++] = 1;
					}
				}
				if(cnt > 3)
					puts("Mario_wins!\n");
				else
				{
					sort(c, c + cnt);
					puts(cnt == 3 && c[2] > 1 || cnt == 2 && (c[0] > 1 || c[1] > 4) || cnt == 1 && c[0] > 7 ? "Mario_wins!\n" : "Wario_wins!\n");
				}
			}
		}
	return 0;
}
