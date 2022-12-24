#include <cmath>
#include <cstdio>
//#include <cassert>
typedef long long LL;
const int maxn = 31623, maxb = 1000000000;
int n, f[maxn];
int sfn(int n)
{
	int ret = 0;
	for(int i = 1, j, k = (int)sqrt(n); i <= k; i = j + 1)
	{
		j = (int)sqrt(n / (n / i / i));
		ret += (n / i / i) * (f[j] - f[i - 1]);
	}
	return ret;
}
LL calc(int n)
{
	LL ret = 0;
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		ret += (j - i + 1) * (n / i - sfn(n / i));
	}
	return ret;
}
int main()
{
	f[1] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		for(int j = i + i; j < maxn; j += i)
			f[j] -= f[i];
		f[i] += f[i - 1];
	}
	int a, b;
	scanf("%d%d", &a, &b); //assert(scanf("%d%d", &a, &b) == 2 && 1 <= a && a <= b && b <= maxb);
	printf("%lld\n", calc(b) - calc(a - 1));
	return 0;
}
