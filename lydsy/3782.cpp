#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxk = 202, pmax = 1000003, maxp = 4, pmod[] = {3, 5, 6793, 10007}, sei[] = {339887755, 407865306, 673070820, 618502650};
int pp, tot, mod, fact[pmax], inv[pmax], f[maxk];
LL n, m;
struct Point
{
	LL x, y;
	bool operator < (const Point &t) const
	{
		return x < t.x || x == t.x && y < t.y;
	}
	bool operator == (const Point &t) const
	{
		return x == t.x && y == t.y;
	}
} a[maxk];
int C(LL n, LL m)
{
	if(n < m)
		return 0;
	if(n >= mod)
		return (LL)C(n / mod, m / mod) * C(n % mod, m % mod) % mod;
	return (LL)fact[n] * inv[fact[m]] * inv[fact[n - m]] % mod;
}
int path(int i, int j)
{
	if(a[i].x > a[j].x || a[i].y > a[j].y)
		return 0;
	return C((a[j].x - a[i].x) + (a[j].y - a[i].y), a[j].x - a[i].x);
}
int calc(int p)
{
	mod = p < maxp ? pmod[p] : pmax;
	fact[0] = 1;
	for(int i = 1; i < mod; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = mod - (LL)mod / i * inv[mod % i] % mod;
	f[0] = 1;
	for(int i = 1; i <= tot + 1; ++i)
	{
		f[i] = path(0, i);
		for(int j = 1; j < i; ++j)
		{
			f[i] -= (LL)f[j] * path(j, i) % mod;
			if(f[i] < 0)
				f[i] += mod;
		}
	}
	return f[tot + 1];
}
int main()
{
	scanf("%lld%lld%d%d", &n, &m, &tot, &pp);
	a[0] = (Point){0, 0};
	for(int i = 1; i <= tot; ++i)
		scanf("%lld%lld", &a[i].x, &a[i].y);
	a[tot + 1] = (Point){n, m};
	sort(a + 1, a + tot + 1);
	tot = unique(a + 1, a + tot + 1) - a - 1;
	if(a[0] == a[1] || a[tot] == a[tot + 1])
	{
		puts("0");
		return 0;
	}
	if(pp == pmax)
		printf("%d\n", calc(maxp));
	else
	{
		LL ans = 0;
		for(int i = 0; i < maxp; ++i)
			ans += (LL)sei[i] * calc(i);
		printf("%d\n", ans % pp);
	}
	return 0;
}
