#include <cstdio>
const int maxn = 1000001, mod = 1000000000;
int n, f[maxn];
int main()
{
	scanf("%d", &n);
	f[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		f[i] = f[i - 1] + (i & 1 ? 0 : f[i >> 1]);
		if(f[i] >= mod)
			f[i] -= mod;
	}
	printf("%d\n", f[n]);
	return 0;
}
