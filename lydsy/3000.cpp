#include <cmath>
#include <cstdio>
typedef long double DB;
const int maxn = 10001;
const DB pi = acos(-1);
int n, k;
DB f[maxn];
int main()
{
	for(int i = 1; i < maxn; ++i)
		f[i] = f[i - 1] + log(i);
	while(scanf("%d%d", &n, &k) != EOF)
		if(n < maxn)
			printf("%d\n", (int)ceil(f[n] / log(k) + 1e-8));
		else
			printf("%lld\n", (long long)((0.5 * log(2 * pi * n) + n * log(n) - n) / log(k)) + 1);
	return 0;
}
