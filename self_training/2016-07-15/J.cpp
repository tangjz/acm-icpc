#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 100001;
int n, m, seed, mod, pw[maxn], a[maxn], bit[maxn];
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
void add(int x, int v)
{
	for( ; x <= n; x += x & -x)
		if((bit[x] += v) >= mod)
			bit[x] -= mod;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		if((ret += bit[x]) >= mod)
			ret -= mod;
	return ret;
}
int main()
{
	while(scanf("%d%d%d%d", &seed, &mod, &n, &m) == 4 && seed + mod + n + m)
	{
		pw[0] = 1;
		for(int i = 1; i <= n; ++i)
			pw[i] = (LL)pw[i - 1] * seed % mod;
		memset(a + 1, 0, n * sizeof(int));
		memset(bit + 1, 0, n * sizeof(int));
		while(m--)
		{
			int x, y, val;
			char op[2];
			scanf("%s%d%d", op, &x, &y);
			if(op[0] == 'E')
			{
				if((val = (LL)(y - a[x]) * pw[n - x] % mod) < 0)
					val += mod;
				add(x, val);
				a[x] = y;
			}
			else
			{
				if((val = (LL)(sum(y) - sum(x - 1)) * mod_inv(pw[n - y]) % mod) < 0)
					val += mod;
				printf("%d\n", val);
			}
		}
		putchar('-');
		putchar('\n');
	}
	return 0;
}
