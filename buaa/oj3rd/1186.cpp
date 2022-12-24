#include <cstdio>
const int maxn = 21;
int n;
long long f[maxn];
int main()
{
	f[1] = 0;
	f[2] = 1;
	for(int i = 3; i < maxn; ++i)
		f[i] = (i - 1) * (f[i - 1] + f[i - 2]);
	while(scanf("%d", &n) == 1)
		printf("%lld\n", f[n]);
	return 0;
}
