#include <cstdio>
const int maxn = 100001, mod = 1000000007;
int n, a[maxn], pos[maxn], f[maxn];
int main()
{
	scanf("%d", &n);
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		f[i] = 2 * f[i - 1] - (pos[a[i]] ? f[pos[a[i]] - 1] : 0);
		if(f[i] >= mod)
			f[i] -= mod;
		if(f[i] < 0)
			f[i] += mod;
		pos[a[i]] = i;
	}
	f[n] -= f[0];
	if(f[n] < 0)
		f[n] += mod;
	printf("%d\n", f[n]);
	return 0;
}
