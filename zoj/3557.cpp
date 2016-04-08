#include <cstdio>
typedef long long LL;
int n, m, p;
int inv(int x)
{
	return x <= 1 ? x : (LL)inv(p % x) * (p - p / x) % p;
}
int C(int n, int m)
{
	if(n < m)
		return 0;
	if(m > n - m)
		return C(n, n - m);
	if(n >= p)
		return (LL)C(n % p, m % p) * C(n / p, m / p) % p;
	int ret = 1;
	for(int i = 0; i < m; ++i)
		ret = (LL)ret * (n - i) % p;
	for(int i = 2; i <= m; ++i)
		ret = (LL)ret * inv(i) % p;
	return ret;
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &p) == 3)
		printf("%d\n", C(n - m + 1, m));
	return 0;
}
