#include <cstdio>
typedef long long LL;
const int maxn = 31623, maxs = 10, mod = 1000000007;
int tot, prime[maxn], m, cnt, p[maxs], e[maxs], ans;
bool vis[maxn];
int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
struct Matrix
{
	int num1, num2;
	bool operator == (const Matrix &x) const
	{
		return num1 == x.num1 && num2 == x.num2;
	}
	Matrix operator * (const Matrix &x) const
	{
		return (Matrix){(int)(((LL)num1 * x.num1 + (LL)num2 * x.num2) % mod),
		(int)(((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % mod)};
	}
	Matrix pow(int k)
	{
		Matrix ret = (Matrix){1, 0}, tmp = *this;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A = {0, 1};
void dfs(int dep, int val, int phi)
{
	if(dep == cnt)
	{
		Matrix B = A.pow(m / val);
		ans = (ans + ((LL)(B.num1 << 1) + B.num2) * phi) % mod;
		return;
	}
	dfs(dep + 1, val, phi);
	for(int i = 1; i <= e[dep]; ++i)
	{
		dfs(dep + 1, val * p[dep], phi * (p[dep] - 1));
		val *= p[dep];
		phi *= p[dep];
	}
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxn; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	int n;
	while(scanf("%d", &n) == 1)
	{
		if(n == 1)
		{
			puts("2");
			continue;
		}
		m = n;
		cnt = 0;
		for(int i = 0; i < tot; ++i)
			if(n % prime[i] == 0)
			{
				for(e[cnt] = 0; n % prime[i] == 0; n /= prime[i], ++e[cnt]);
				p[cnt++] = prime[i];
			}
		if(n > 1)
		{
			e[cnt] = 1;
			p[cnt++] = n;
		}
		ans = 0;
		dfs(0, 1, 1);
		ans = (LL)ans * mod_inv(m) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
