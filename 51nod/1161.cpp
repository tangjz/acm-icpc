#include <cstdio>
const int maxn = 5010, mod = 1000000007;
typedef long long LL;
int n, m, inv[maxn], f[maxn];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int C(int x, int y)
{
	if(x < y)
		return 0;
	int ret = 0;
	for(int i = 0; i < y; ++i)
		ret = (LL)ret * (x - i) % mod;
	for(int i = 1; i <= y; ++i)
		ret = (LL)ret * inv[i] % mod;
	return ret;
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", f + i);
	for(int i = n - 1; i >= 0; --i)
		for(int j = 1; j <= i; ++j)
			inc(f[i], (LL)f[i - j] * C(m - 1 + j, j) % mod);
	for(int i = 0; i < n; ++i)
		printf("%d\n", f[i]);
	return 0;
}
