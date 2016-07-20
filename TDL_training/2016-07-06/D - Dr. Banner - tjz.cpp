#include <cstdio>
const int maxn = 100001, mod = 1000000007;
int n, f[maxn];
int main()
{
	scanf("%d", &n);
	f[1] = 1;
	for(int i = 2; i < n; ++i)
	{
		f[i] = f[i >> 1] + f[i - 1] + 1;
		if(f[i] >= mod)
			f[i] -= mod;
	}
	printf("%d\n", f[n >> 1] + 1);
	return 0;
}
