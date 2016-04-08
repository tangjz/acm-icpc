/*
 * \sum_{i = 1}^n{\sum_{j = 1}^m{[gcd(i, j) = d]}}
 * = \sum_{i = 1}^n{\sum_{j = 1}^m{\sum_{d|gcd(i, j)}{mu(d)}}}
 * = [n / d] * [m / d] * \sum_{d = 1}^min(n, m){mu(d)}
 * 线性筛预处理莫比乌斯函数mu[]
 * 每次询问是有关mu[]前缀和的分块>_< 
 */
#include <cstdio>
const int maxv = 50001;
int cnt, prime[maxv], mu[maxv], smu[maxv], ans;
bool vis[maxv];
int main()
{
	mu[1] = smu[1] = 1;
	for(int i = 2; i < maxv; ++i)
	{
		if(!vis[i])
		{
			prime[cnt++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < cnt && i * prime[j] < maxv; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else mu[i * prime[j]] = -mu[i];
		}
		smu[i] = smu[i - 1] + mu[i];
	}
	int n, a, b, d;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d%d%d", &a, &b, &d);
		a /= d, b /= d;
		if(a > b) { int t = a; a = b; b = t; }
		ans = 0;
		for(int i = 1, j; i <= a; i = j + 1)
		{
			j = a / (a / i) < b / (b / i) ? a / (a / i) : b / (b / i);
			ans += (smu[j] - smu[i - 1]) * (a / i) * (b / i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
