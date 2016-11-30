#include <cmath>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxp = 31623, hmod = 5552263, maxm = 2000010;
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
	int a, b;
	exgcd(x, p, a, b);
	if(a < 0)
		a += p;
	return a;
}
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	while(k > 0)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
struct HashTable
{
	int tot, ctr, lnk[hmod], nxt[maxm], val[maxm], idx[maxm];
	void init()
	{
		tot = ctr = 0;
		memset(lnk, -1, sizeof lnk);
	}
	void insert(int id, int v)
	{
		++ctr;
		int pos = v % hmod;
		for(int it = lnk[pos]; it != -1; it = nxt[it])
			if(val[it] == v)
				return;
		assert(tot < maxm);
		nxt[tot] = lnk[pos];
		val[tot] = v;
		idx[tot] = id;
		lnk[pos] = tot++;
	}
	int find(int v)
	{
		int pos = v % hmod;
		for(int it = lnk[pos]; it != -1; it = nxt[it])
			if(val[it] == v)
				return idx[it];
		return -1;
	}
} H, H2;
int bsgs(int a, int p, int b, int ord, HashTable &Hash) // a^x mod p = b, a^ord mod p = 1, (a, p) = 1
{
	if(p == 1)
		return 1;
	int size = Hash.ctr, block = ord / size + 1;
	for(int i = 0, delta = mod_inv(mod_pow(a, size, p), p), tmp = b; i <= block; ++i, tmp = (LL)tmp * delta % p)
	{
		int tp = Hash.find(tmp);
		if(tp != -1)
			return i * size + tp;
	}
	return -1;
}
int t, seed, p, n, k;
int main()
{
	static int tot = 0, prime[maxp], d[maxp] = {};
	for(int i = 2; i < maxp; ++i)
	{
		if(!d[i])
			prime[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * prime[j]) < maxp; ++j)
		{
			d[k] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &seed, &p, &n, &k);
		int tmp = p - 1, ord = p - 1;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
			{
				for(tmp /= prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
				for( ; ord % prime[i] == 0 && mod_pow(seed, ord / prime[i], p) == 1; ord /= prime[i]);
			}
		if(tmp > 1 && mod_pow(seed, ord / tmp, p) == 1)
			ord /= tmp;
		int delta = 0, pw2 = 1, ans = -1;
		for(int now = seed; ~ord & 1; ord >>= 1, pw2 <<= 1, ++delta)
		{
			now = (LL)now * now % p;
			if(now % n == k)
			{
				ans = delta + 1;
				break;
			}
		}
		if(ans != -1)
		{
			printf("%d\n", ans);
			continue;
		}
		tmp = ord;
		int ord2 = tmp;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
			{
				for(tmp /= prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
				ord2 -= ord2 / prime[i];
			}
		if(tmp > 1)
			ord2 -= ord2 / tmp;
		tmp = ord2;
		for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
			if(tmp % prime[i] == 0)
			{
				for(tmp /= prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
				for( ; ord2 % prime[i] == 0 && mod_pow(2, ord2 / prime[i], ord) == 1; ord2 /= prime[i]);
			}
		if(tmp > 1 && mod_pow(2, ord2 / tmp, ord) == 1)
			ord2 /= tmp;
		int bound = (int)ceil(pow(p >> 1, 2.0 / 3) + 0.5);
		if(k <= bound)
   			for(int i = 1, now = mod_pow(seed, 1 << delta, p); i <= ord2; ++i)
   			{
   				now = (LL)now * now % p;
   				if(now % n == k)
   				{
   					ans = delta + i;
   					break;
   				}
   			}
		else
		{
			{ // init H with seed mod p
				HashTable &Hash = H;
				Hash.init();
				int size = bound;
				for(int i = 1, tmp = seed; i <= size; ++i, tmp = (LL)tmp * seed % p)
					Hash.insert(i, tmp);
			}
			{ // init H2 with 2 mod ord
				HashTable &Hash = H2;
				Hash.init();
				int size = bound;
				for(int i = 1, tmp = 2; i <= size; ++i, tmp = (LL)tmp * 2 % ord)
					Hash.insert(i, tmp);
			}
			for(int val = k; val < p; val += n)
			{
				int ordv = bsgs(seed, p, val, ord << delta, H);
				if(ordv == -1 || ordv & (pw2 - 1))
					continue;
				ordv >>= delta;
				int ordv2 = bsgs(2, ord, ordv, ord2, H2);
				if(ans == -1 || ordv2 != -1 && ans > ordv2)
					ans = ordv2;
			}
			if(ans != -1)
				ans += delta;
		}
		printf("%d\n", ans);
	}
	return 0;
}
