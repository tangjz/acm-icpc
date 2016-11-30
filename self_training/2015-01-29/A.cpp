#include <cstdio>
int pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % p;
		x = (long long)x * x % p;
		k >>= 1;
	}
	return ret;
}
int n, k;
int main()
{
	while(scanf("%d%d", &n, &k) == 2 && n && k)
		printf("%d\n", pow(2008, (pow(2,3 * n + 1, 250 * k) + 250 * k - 1ll) * (pow(251, n + 1, 250 * k) + 250 * k - 1ll) % (250 * k) / 250, k));
	return 0;
}
