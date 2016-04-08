/*
 * gcd(fib_i, fib_{i + 1}) = gcd(fib_{i - 1}, fib_i) = ... = gcd(fib_1, fib_2) = 1
 * fib_{n + m} = fib_{n - 1} * fib_m + fib_n * fib_{m + 1}
 * 所以 gcd(fib_{n + m}, fib_n) = gcd(fib_{n - 1} * fib_m, fib_n) = gcd(fib_{n - 1}, fib_n) * gcd(fib_m, fib_n) = gcd(fib_m, fib_n)
 * 所以 gcd(fib_i, fib_j) = fib_{gcd(i, j)}
 * 所以 fib_j | fib_i 等价于 j | i
 * 记e[i]为i的最小质因数次数，d[i]为i除去最小质因数的数，g[i]为i的因数个数，f[i]为i的因数平方和 
 * 对于欧式筛中i mod prime[j]为0的情况:
 * 最小质因数+1，因数个数关于最小质因数部分重算，d[]不变，f[]为f[i] * prime[j] ^ 2 + f[d[]]
 * 对于i mod prime[j]非0的情况:
 * 遇见的是最小质因数，因数个数翻倍，f[]为f[i] * prime[j] ^ 2 + f[i]
 * 注意fib_1 = fib_2 = 1 
 */
#include <cstdio>
typedef long long LL;
const int maxc = 664580, maxv = 10000001, mod = 1000000007;
int cnt, prime[maxc], e[maxv], d[maxv], g[maxv], f[maxv], sumg, sumf;
bool vis[maxv];
int main()
{
	int Q, q, A, B, C;
	scanf("%d%d%d%d%d", &Q, &q, &A, &B, &C);
	A %= C, B %= C;
	g[1] = f[1] = 1;
	for(int i = 2; i <= C; ++i)
	{
		if(!vis[i])
		{
			prime[cnt++] = i;
			e[i] = d[i] = 1;
			g[i] = 2;
			f[i] = ((LL)i * i + 1) % mod;
		}
		for(int j = 0, k; j < cnt && (k = i * prime[j]) <= C; ++j)
		{
			vis[k] = 1;
			if(i % prime[j] == 0)
			{
				e[k] = e[i] + 1;
				g[k] = (g[i] / (e[i] + 1)) * (e[k] + 1);
				d[k] = d[i];
				f[k] = (f[i] * ((LL)prime[j] * prime[j] % mod) + f[d[i]]) % mod;
				break;
			}
			else
			{
				e[k] = 1;
				d[k] = i;
				g[k] = g[i] << 1;
				f[k] = f[i] * (((LL)prime[j] * prime[j] + 1) % mod) % mod;
			}
		}
	}
	while(Q--)
	{
		sumg += g[q] + (q & 1);
		sumf += f[q] + 4 * (q & 1);
		if(sumg >= mod) sumg -= mod;
		if(sumf >= mod) sumf -= mod;
		q = (q * (LL)A + B) % C + 1;
	}
	printf("%d\n%d\n", sumg, sumf);
	return 0;
}
