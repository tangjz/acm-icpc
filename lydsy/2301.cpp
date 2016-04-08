#include <cstdio>
const int maxn = 50001;
int t, tot, prime[maxn], mu[maxn], smu[maxn];
bool vis[maxn];
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(int x)
{
	if(!x)
	{
		puts("0");
		return;
	}
	int len = 0, num[10];
	while(x)
	{
		num[len++] = x % 10;
		x /= 10;
	}
	while(len)
		putchar('0' + num[--len]);
	putchar('\n');
}
long long calc(int n, int m, int k)
{
	long long ret = 0;
	n /= k;
	m /= k;
	if(n > m)
		swap(n, m);
	for(int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i) < m / (m / i) ? n / (n / i) : m / (m / i);
		ret += (long long)(n / i) * (m / i) * (smu[j] - smu[i - 1]);
	}
	return ret;
}
int main()
{
	mu[1] = smu[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < tot && i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
		smu[i] = smu[i - 1] + mu[i];
	}
	scan(t);
	while(t--)
	{
		int a, b, c, d, k;
		scan(a), scan(b), scan(c), scan(d), scan(k);
		print(calc(b, d, k) - calc(a - 1, d, k) - calc(b, c - 1, k) + calc(a - 1, c - 1, k));
	}
	return 0;
}
