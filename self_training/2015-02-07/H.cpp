#include <cstdio>
const int mod = 1000000007, maxn = 10000010;
int n, m, fa[maxn], tot;
int pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		tot = 0;
		for(int i = 1; i <= n + 1; ++i)
			fa[i] = i;
		while(m--)
		{
			int l, r;
			scanf("%d%d", &l, &r);
			if((l = find(l)) != (r = find(r + 1)))
			{
				fa[l] = r;
				++tot;
			}
		}
		printf("%d\n", pow(26, n - tot));
	}
	return 0;
}
