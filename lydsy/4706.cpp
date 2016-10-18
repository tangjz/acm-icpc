#include <stdio.h>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int n, inv[maxn + 1], f[maxn];
int main()
{
	scanf("%d", &n);
	if((n -= 2) <= 0)
	{
		puts("0");
		return 0;
	}
	inv[1] = f[0] = f[1] = 1;
	for(int i = 2; i <= n + 1; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 2; i <= n; ++i)
		f[i] = ((6 * i - 3LL) * f[i - 1] - (i - 2LL) * f[i - 2]) % mod * inv[i + 1] % mod;
	if(f[n] < 0)
		f[n] += mod;
	printf("%d\n", f[n]);
	return 0;
}
