#include <cstdio>
typedef long long LL;
const int maxn = 50001;
int tot, prime[maxn], d[maxn], c[maxn], f[maxn], g[maxn], t, n, m;
LL ans;
template<class T> void scan(T& x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
template<class T> void print(T x)
{
	int len = 0, num[20];
	for( ; x; x /= 10)
		num[len++] = x % 10;
	if(!len)
		num[len++] = 0;
	while(len)
		putchar('0' + num[--len]);
	putchar('\n');
}
int main()
{
	f[1] = g[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!g[i])
		{
			prime[tot++] = i;
			d[i] = 1;
			c[i] = 1;
			f[i] = -1;
			g[i] = 2;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			int o = i * prime[j];
			if(i % prime[j] == 0)
			{
				d[o] = d[i];
				c[o] = c[i] + 1;
				f[o] = 0;
				g[o] = g[d[o]] * (c[o] + 1);
				break;
			}
			else
			{
				d[o] = i;
				c[o] = 1;
				f[o] = -f[i];
				g[o] = g[d[o]] * (c[o] + 1);
			}
		}
	}
	for(int i = 2; i < maxn; ++i)
	{
		f[i] += f[i - 1];
		g[i] += g[i - 1];
	}
	scan(t);
	while(t--)
	{
		ans = 0;
		scan(n), scan(m);
		if(n > m)
		{
			n = n + m;
			m = n - m;
			n = n - m;
		}
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i) < m / (m / i) ? n / (n / i) : m / (m / i);
			ans += (LL)(f[j] - f[i - 1]) * g[n / i] * g[m / i];
		}
		print(ans);
	}
	return 0;
}
