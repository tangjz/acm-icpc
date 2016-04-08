#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 32000, mod = 66601;
typedef long long LL;
int tot, prime[maxn], t, p, a, b, g, cnt, pre[mod], ans[maxn];
bool vis[maxn];
struct Hash
{
	int nxt, val, id;
} e[maxn];
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
int inv(int x, int p)
{
	return x <= 1 ? x : (LL)inv(p % x, p) * (p - p / x) % p;
}
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int bsgs(int x, int p, int y)
{
	int size = (int)ceil(sqrt(p + 0.01));
	cnt = 0;
	memset(pre, -1, sizeof pre);
	for(int i = 0, now = 1; i < size; ++i)
	{
		bool flag = 0;
		for(int it = pre[now % mod]; it != -1; it = e[it].nxt)
			if(e[it].val == now)
			{
				flag = 1;
				break;
			}
		if(!flag)
		{
			e[cnt] = (Hash){pre[now % mod], now, i};
			pre[now % mod] = cnt++;
		}
		now = (LL)now * x % p;
	}
	int z = inv(mod_pow(x, size, p), p);
	for(int i = 0, now = y; i < size; ++i)
	{
		for(int it = pre[now % mod]; it != -1; it = e[it].nxt)
			if(e[it].val == now)
				return i * size + e[it].id;
		now = (LL)now * z % p;
	}
	return -1;
}
bool ori(int x, int p)
{
	int ord = p - 1, now = p - 1;
	for(int i = 0; i < tot && (LL)prime[i] * prime[i] <= now; ++i)
		if(now % prime[i] == 0)
		{
			if(ord % prime[i] == 0 && mod_pow(g, ord / prime[i], p) == 1)
				return 0;
			while(now % prime[i] == 0)
				now /= prime[i];
		}
	if(now > 1 && mod_pow(g, ord / now, p) == 1)
		return 0;
	return 1;
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && (LL)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d%d%d", &p, &a, &b);
	for(g = 2; ; ++g)
		if(ori(g, p))
			break;
	int w = bsgs(g, p, b);
	int u = a, v = p - 1, x, y;
	int r = exgcd(u, v, x, y);
	if(w == -1 || w % r != 0)
	{
		puts("0");
		return 0;
	}
	u /= r;
	v /= r;
	w /= r;
	x = (LL)x * w % v;
	if(x < 0)
		x += v;
	for(int i = 0; i < r; ++i, x += v)
		ans[i] = mod_pow(g, x, p);
	sort(ans, ans + r);
	printf("%d\n", r);
	for(int i = 0; i < r; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
