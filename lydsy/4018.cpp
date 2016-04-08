#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2000001, mod1 = 1000000007, mod2 = 1000000009;
int t, n, m, p, q, tot, prime[maxn], sf[maxn][2], ans[2];
bool vis[maxn];
void inc(int &x, int y, int mod)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int f(int A, int B, int mod)
{
	if(!A || !B)
		return 0;
	if(A > B)
		swap(A, B);
	int cnt1 = (long long)(A - 1) * A * (A + 1) / 3 % mod;
	int cnt2 = (long long)A * B * (B - A) / 2 % mod;
	inc(cnt1, cnt2, mod);
	return cnt1;
}
int main()
{
	sf[1][0] = sf[1][1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			sf[i][0] = mod1 - i + 1;
			sf[i][1] = mod2 - i + 1;
		}
		for(int j = 0; j < tot && (long long)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				sf[i * prime[j]][0] = sf[i][0];
				sf[i * prime[j]][1] = sf[i][1];
				break;
			}
			else
			{
				sf[i * prime[j]][0] = (long long)sf[i][0] * sf[prime[j]][0] % mod1;
				sf[i * prime[j]][1] = (long long)sf[i][1] * sf[prime[j]][1] % mod2;
			}
		}
	}
	for(int i = 2; i < maxn; ++i)
	{
		inc(sf[i][0], sf[i - 1][0], mod1);
		inc(sf[i][1], sf[i - 1][1], mod2);
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(n > m)
			swap(n, m);
		ans[0] = ans[1] = 0;
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = min(n / (n / i), m / (m / i));
			inc(ans[0], (long long)(sf[j][0] - sf[i - 1][0] + mod1) * f(n / i, m / i, mod1) % mod1, mod1);
			inc(ans[1], (long long)(sf[j][1] - sf[i - 1][1] + mod2) * f(n / i, m / i, mod2) % mod2, mod2);
		}
		printf("%d %d\n", ans[0], ans[1]);
	}
	return 0;
}
