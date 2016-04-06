#include <stdio.h>
const int mod = 10007;
int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * mod_inv(mod % x) % mod;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}
struct Node
{
	int res, exp;
	Node operator + (const Node &x) const
	{
		return (Node){res * x.res % mod, exp + x.exp};
	}
	Node operator - (const Node &x) const
	{
		return (Node){res * mod_inv(x.res) % mod, exp - x.exp};
	}
	Node operator * (const int &x) const
	{
		return (Node){mod_pow(res, x), exp * x};
	}
} ;
int fact[mod];
Node mod_fact(int n)
{
	return n ? mod_fact(n / mod) + (Node){(n / mod) & 1 ? mod - fact[n % mod] : fact[n % mod], n / mod} : (Node){1, 0};
}
int calc(int n, int d)
{
	Node ret = mod_fact(n / d) - mod_fact(d - 1);
	ret = ret * d;
	for(int i = 1, j, e = n / d + d; i < d; ++i)
	{
		Node tmp = (Node){1, 0};
		for(j = i; j % mod == 0; j /= mod, ++tmp.exp);
		tmp.res = tmp.res * j % mod;
		for(j = e - i; j % mod == 0; j /= mod, ++tmp.exp);
		tmp.res = tmp.res * j % mod;
		ret = ret + tmp * i;
	}
	ret = mod_fact(n) - ret;
	return ret.exp ? 0 : ret.res;
}
int main()
{
	fact[0] = 1;
	for(int i = 1; i < mod; ++i)
		fact[i] = fact[i - 1] * i % mod;
	int n, ans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n / i; ++i)
		if(n % i == 0)
			ans += (1 + (i < n / i)) * calc(n, i);
	printf("%d\n", ans % mod);
	return 0;
}
