#include <cstdio>
typedef long long LL;
const int maxn = 5000001, maxs = 348513;
int tot, prime[maxn], phi[maxn];
long long f[maxn];
void scan(int &x)
{
    int ch;
    while((ch = getchar()) < '0' || ch > '9');
    x = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch - '0');
}
void print(LL x)
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
	phi[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!phi[i])
		{
			prime[tot++] = i;
			phi[i] = i - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
	}
	for(int i = 1; i < maxn; ++i)
		for(int j = i + i; j < maxn; j += i)
			f[j] += i * phi[j / i];
	for(int i = 1; i < maxn; ++i)
		f[i] += f[i - 1];
	int t, n;
	scan(t);
	while(t--)
	{
		scan(n);
		print(f[n]);
	}
	return 0;
}
