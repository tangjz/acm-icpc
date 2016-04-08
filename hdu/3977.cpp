#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxs = 1000000;
int p;
void inc(int &x, int y)
{
	x += y;
	if(x >= p)
		x -= p;
}
void dec(int &x, int y)
{
	x -= y;
	if(x < 0)
		x += p;
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
		return (Matrix){((LL)num1 * x.num1 + (LL)num2 * x.num2) % p,
		((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % p};
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
} A = {0, 1}, I = {1, 0};
int tot, prime[maxs], pans[maxs] = {0, 0, 3, 8, 0, 20};
bool vis[maxs];
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int solve(int n)
{
	if(n < maxs && pans[n])
		return pans[n];
	p = n;
	n = mod_pow(5, p - 1 >> 1) == 1 ? p - 1 : (p + 1 << 1);
	int ret = n;
	for(int i = 0; i < tot && (LL)prime[i] * prime[i] <= n; ++i)
	    if(n % prime[i] == 0)
	    {
            while(ret % prime[i] == 0 && A.pow(ret / prime[i]) == I)
                ret /= prime[i];
            while(n % prime[i] == 0)
                n /= prime[i];
	    }
    if(n > 1 && A.pow(ret / n) == I)
        ret /= n;
	if(p < maxs)
		pans[p] = ret;
	return ret;
}
LL gcd(LL x, LL y)
{
	return y ? gcd(y, x % y) : x;
}
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(LL &x)
{
	if(!x)
	{
		puts("0");
		return;
	}
	int len = 0, num[18];
	while(x)
	{
		num[len++] = x % 10;
		x /= 10;
	}
	while(len)
		putchar('0' + num[--len]);
	putchar('\n');
}
int main()
{
	for(int i = 2; i < maxs; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && (LL)i * prime[j] < maxs; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	int t, n;
	scan(t);
	for(int Case = 1; Case <= t; ++Case)
	{
		LL ans = 1;
		scan(n);
		for(int i = 0; i < tot && (LL)prime[i] * prime[i] <= n; ++i)
			if(n % prime[i] == 0)
			{
				LL tmp = solve(prime[i]);
				for(n /= prime[i]; n % prime[i] == 0; n /= prime[i])
					tmp *= prime[i];
				ans = ans / gcd(ans, tmp) * tmp;
			}
		if(n > 1)
		{
			LL tmp = solve(n);
			ans = ans / gcd(ans, tmp) * tmp;
		}
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}
