#include <cstdio>
const int maxn = 20188, mod = 100007;
int f[maxn] = {1, 2}, n;
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		f[i] = f[i - 1] + f[i - 2];
		if(f[i] >= mod)
			f[i] -= mod;
	}
	while(scanf("%d", &n) == 1)
		printf("%d\n", f[n % maxn]);
	return 0;
}
