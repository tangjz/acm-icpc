#include <cstdio>
const int maxn = 233333;
int n, f[maxn], bit[maxn];
long long ans, ans1, ans2;
void update(int x, int val)
{
	for( ; x <= n << 1; x += x & -x)
		bit[x] += val;
}
int query(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	scanf("%d", &n);
	ans = (long long)n * (n - 1) / 2 * (n - 2) / 3;
	for(int i = 0, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		f[u] = v;
		f[v] = u;
	}
	for(int i = 1; i <= n << 1; ++i)
	{
		if(i < f[i])
			continue;
		int x = query(i) - query(f[i] - 1);
		int z = i - f[i] - 1 - x * 2;
		int y = n - 1 - x - z;
		update(f[i], 1);
		ans1 += (long long)z * (x + y);
		ans2 += (long long)x * y;
	}
	printf("%I64d\n", ans - ans1 / 2 - ans2);
	return 0;
}
