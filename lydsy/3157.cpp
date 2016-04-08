/*
 * Let S_k = \sum_{i = 1}^n{i ^ k * m ^ i}
 * Obviously, S_0 = \sum_{i = 1}^n{m ^ i} = \frac{m ^ {n + 1} - m}{m - 1}
 * Now we attempt to simplify S_k
 * (m - 1) * S_k
 * = \sum_{i = 1}^n{i ^ k * m ^ {i + 1}} - \sum_{i = 1}^n{i ^ k * m ^ i}
 * = \sum_{i = 1}^{n + 1}{(i - 1) ^ k * m ^ {i + 1}} - \sum_{i = 1}^n{i ^ k * m ^ i}
 * = n ^ k * m ^ {n + 1} + \sum_{i = 1}^n{((i - 1) ^ k - i ^ k) * m ^ i}
 * = n ^ k * m ^ {n + 1} + \sum_{i = 1}^n{\sum_{j = 0}^{k - 1}{(-1) ^ {k - j} * \binom{k}{j} * i ^ j} * m ^ i}
 * = n ^ k * m ^ {n + 1} + \sum_{j = 0}^{k - 1}{(-1) ^ {k - j} * \binom{k}{j} * \sum_{i = 1}^n{i ^ j * m ^ i}}
 * = n ^ k * m ^ {n + 1} + \sum_{j = 0}^{k - 1}{(-1) ^ {k - j} * \binom{k}{j} * S_j}
 * Since p is a prime number, this problem is solved in O(m ^ 2) time.
 */
#include <cstdio>
typedef long long LL;
const int mod = 1000000007, maxm = 1001;
int n, m, c[maxm][maxm], s[maxm];
inline int pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1) ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	if(m == 1)
	{
		printf("%d\n", ((LL)n * (n + 1) / 2) % mod);
		return 0;
	}
	for(int i = 1; i <= m; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			if(c[i][j] >= mod) c[i][j] -= mod;
		}
	}//Actually, preproccessing i! mod p(1<=i<=m) is a faster method provided that p is a prime number...
	int inv = pow(m - 1, mod - 2);
	s[0] = ((LL)pow(m, n + 1) - m + mod) * inv % mod;
	for(int i = 1; i <= m; ++i)
	{
		s[i] = (LL)pow(n, i) * pow(m, n + 1) % mod;
		for(int j = 0; j < i; ++j)
		{
			s[i] = (s[i] + ((i - j) & 1 ? -1 : 1) * (LL)c[i][j] * s[j]) % mod;
			if(s[i] < 0) s[i] += mod; 
		}
		s[i] = (LL)s[i] * inv % mod;
	}
	printf("%d\n", s[m]);
	return 0;
}
