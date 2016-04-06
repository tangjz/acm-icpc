#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100002, mod = 1000000007;
int n, c[maxn], f[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		++c[x];
	}
	for(int i = 1; i < n; ++i)
		c[i] += c[i - 1];
	f[1] = 1;
	for(int i = 2; i <= n; ++i)
		f[i] = mod - mod / i * (LL)f[mod % i] % mod;
	for(int i = 1; i <= n - i + 1; ++i)
		swap(f[i], f[n - i + 1]);
	f[0] = 1;
	for(int i = 2; i <= n; ++i)
		f[0] = (LL)f[0] * i % mod;
	for(int i = 0; i < n; ++i)
		f[i + 1] = (LL)f[i] * (c[i] - i) % mod * f[i + 1] % mod;
	for(int i = 0; i <= n; ++i)
		ans = (ans + (LL)i * (f[i] - f[i + 1])) % mod;
	printf("%d\n", ans);
	return 0;
}
