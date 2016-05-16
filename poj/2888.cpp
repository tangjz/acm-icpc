#include <cstdio>
#include <cstring>
const int maxn = 10, maxp = 31623, maxs = 11, mod = 9973;
struct Matrix
{
	int r, c, num[maxn][maxn];
	Matrix operator * (const Matrix &t) const
	{
		Matrix ret = {r, t.c};
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < t.c; ++k)
					ret.num[i][k] = (ret.num[i][k] + num[i][j] * t.num[j][k]) % mod;
		return ret;
	}
	Matrix pow(int k)
	{
		Matrix ret = {r, r}, tmp = *this;
		for(int i = 0; i < r; ++i)
			ret.num[i][i] = 1;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A, B;
int inv[mod], tot, prime[maxp], t, n, m, q, cnt, p[maxs], c[maxs], ans;
bool vis[maxp];
void dfs(int dep, int val, int phi)
{
	if(dep == cnt)
	{
		B = A.pow(n / val);
		int tmp = 0;
		for(int i = 0; i < m; ++i)
			if((tmp += B.num[i][i]) >= mod)
				tmp -= mod;
		ans = (ans + (long long)tmp * phi) % mod;
		return;
	}
	dfs(dep + 1, val, phi);
	for(int i = 1; i <= c[dep]; ++i)
		dfs(dep + 1, val *= p[dep], phi *= p[dep] - (i == 1));
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	for(int i = 2; i < maxp; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxp; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &q);
		A.r = A.c = m;
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < m; ++j)
				A.num[i][j] = 1;
		while(q--)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			--a;
			--b;
			A.num[a][b] = A.num[b][a] = 0;
		}
		{
			int tmp = n;
			cnt = 0;
			for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
				if(tmp % prime[i] == 0)
				{
					for(c[cnt] = 1, tmp /= prime[i]; tmp % prime[i] == 0; ++c[cnt], tmp /= prime[i]);
					p[cnt++] = prime[i];
				}
			if(tmp > 1)
			{
				c[cnt] = 1;
				p[cnt++] = tmp;
			}
		}
		ans = 0;
		dfs(0, 1, 1);
		ans = ans * inv[n % mod] % mod;
		printf("%d\n", ans);
	}
	return 0;
}
