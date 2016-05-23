#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int n, inv[maxn], f[maxn];
int main()
{
	scanf("%d", &n);
	inv[1] = f[0] = f[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
		f[i] = (2 * f[i - 1] + 3 * (i - 2) * (LL)inv[i] % mod * f[i - 2]) % mod;
	}
	printf("%d\n", f[n]);
	return 0;
}
