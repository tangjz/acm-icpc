#include <cstdio>
const int maxn = 101, mod = 2007;
int f[maxn];
int main()
{
	for(int i = 1, pw = 1; i < maxn; ++i, pw = pw * 5 % mod)
		f[i] = pw * 4 * i % mod;
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
