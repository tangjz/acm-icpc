#include <cstdio>
const int maxn = 100001, mod = 1000000007;
int f[maxn], t, n;
int main()
{
	f[0] = 1;
	for(int i = 1; i < maxn; ++i)
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
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
