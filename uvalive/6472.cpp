#include <cstdio>
typedef long long LL;
int t, id, p, n, m;
LL Pow(LL x, LL k)
{
	LL ret = 1;
	while(k)
	{
		if(k & 1)
			ret *= x;
		x *= x;
		k >>= 1;
	}
	return ret;
}
LL C(LL n, LL m)
{
	LL ret = 1;
	if(n - m < m)
		m = n - m;
	for(int i = 0; i < m; ++i)
	{
		ret *= n - i;
		ret /= i + 1;
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &id, &p, &n, &m);
		printf("%d %lld\n", id, C(n, m) * Pow(p, n - m));
	}
	return 0;
}
