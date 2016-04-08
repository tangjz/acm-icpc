#include <cstdio>
const int maxn = 50001, mod = 1000000007;
int n, f[maxn];
int main()
{
	scanf("%d", &n);
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		long long tmp = 0;
		for(int j = 1; j * (3 * j - 1) >> 1 <= i; ++j)
			if(j & 1)
				tmp += f[i - (j * (3 * j - 1) >> 1)];
			else
				tmp -= f[i - (j * (3 * j - 1) >> 1)];
		for(int j = 1; -j * (3 * -j - 1) >> 1 <= i; ++j)
			if(j & 1)
				tmp += f[i - (-j * (3 * -j - 1) >> 1)];
			else
				tmp -= f[i - (-j * (3 * -j - 1) >> 1)];
		f[i] = tmp % mod;
		if(f[i] < 0)
			f[i] += mod;
	}
	printf("%d\n", f[n]);
	return 0;
}
