#include <stdio.h>
#include <cassert>
#include <algorithm>
typedef long long LL;
const int maxn = 1234569, maxs = 1001, mod = 1000000007;
int tot, pr[maxn >> 3 | 1], d[maxn], phi[maxn], n, sz[2], seq[2][maxs];
void factor(int n, int &sz, int seq[])
{
	sz = 0;
	for(int i = 1; i * i <= n; ++i)
		if(n % i == 0)
			seq[sz++] = i;
	int tp = sz - 1;
	if(seq[tp] * seq[tp] == n)
		--tp;
	for( ; tp >= 0; --tp)
		seq[sz++] = n / seq[tp];
}
int solve(int sz, int seq[])
{
	int ret = 0;
	for(int i = 0; i < sz; ++i)
		ret = (ret + (LL)seq[i] * phi[seq[i]]) % mod;
	return ret;
}
inline int lcm(int x, int y)
{
	return x / std::__gcd(x, y) * y;
}
int solve(int sz1, int seq1[], int sz2, int seq2[])
{
	int ret = solve(sz1, seq1) + solve(sz2, seq2);
	if(ret >= mod)
		ret -= mod;
	for(int i = 0; i < sz1; ++i)
		for(int j = 0; j < sz2; ++j)
			ret = (ret + (LL)phi[seq1[i]] * phi[seq2[j]] % mod * lcm(seq1[i], seq2[j])) % mod;
	return ret;
}
int main()
{
	scanf("%d", &n);
	phi[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			phi[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				phi[k] = phi[i] * pr[j];
				break;
			}
			else
				phi[k] = phi[i] * (pr[j] - 1);
		}
	}
	if(d[n] == n)
	{
		factor(n - 1, sz[0], seq[0]);
		printf("%d\n", solve(sz[0], seq[0]));
	}
	else
	{
		int x = d[n], y = n / d[n];
		assert(d[y] == y);
		factor(x - 1, sz[0], seq[0]);
		factor(y - 1, sz[1], seq[1]);
		printf("%d\n", solve(sz[0], seq[0], sz[1], seq[1]));
	}
	return 0;
}
