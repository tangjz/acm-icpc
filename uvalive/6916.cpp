#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2000010, maxk = 100, mod = 997;
int t, n, m, tot, fact[maxn][2], inv[mod], f[maxk];
struct Point
{
	int x, y;
	bool operator < (const Point &t) const
	{
		return x < t.x || x == t.x && y < t.y;
	}
	bool operator == (const Point &t) const
	{
		return x == t.x && y == t.y;
	}
} a[maxk];
int C(int n, int m)
{
	if(n < m)
		return 0;
	int p = fact[n][1] - fact[m][1] - fact[n - m][1];
	if(p > 0)
		return 0;
	return fact[n][0] * inv[fact[m][0]] * inv[fact[n - m][0]] % mod;
}
int path(int i, int j)
{
	if(a[i].x > a[j].x || a[i].y > a[j].y)
		return 0;
	return C((a[j].x - a[i].x) + (a[j].y - a[i].y), a[j].x - a[i].x);
}
int main()
{
	fact[0][0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		int j = i;
		while(j % mod == 0)
		{
			++fact[i][1];
			j /= mod;
		}
		fact[i][0] = fact[i - 1][0] * j % mod;
		fact[i][1] += fact[i - 1][1];
	}
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		int k;
		tot = 0;
		scanf("%d%d%d", &n, &m, &k);
		for(int i = 1; i <= k; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			for(int xx = x - 1; xx <= x + 1; ++xx)
				for(int yy = y - 1; yy <= y + 1; ++yy)
					if(xx >= 1 && xx <= n && yy >= 1 && yy <= m)
						a[++tot] = (Point){xx, yy};
		}
		sort(a + 1, a + tot + 1);
		tot = unique(a + 1, a + tot + 1) - a - 1;
		if(a[1].x == 1 && a[1].y == 1 || a[tot].x == n && a[tot].y == m)
		{
			printf("Case #%d: 0\n", Case);
			continue;
		}
		a[0] = (Point){1, 1};
		a[tot + 1] = (Point){n, m};
		f[0] = 1;
		for(int i = 1; i <= tot + 1; ++i)
		{
			f[i] = path(0, i);
			for(int j = 1; j < i; ++j)
			{
				f[i] -= f[j] * path(j, i) % mod;
				if(f[i] < 0)
					f[i] += mod;
			}
		}
		printf("Case #%d: %d\n", Case, f[tot + 1]);
	}
	return 0;
}
