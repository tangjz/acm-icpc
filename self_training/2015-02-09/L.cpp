#include <cstdio>
const int maxc = 301;
typedef unsigned long long ULL;
int t, c, phi[maxc], mod[maxc];
ULL a, b, n;
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int pow(int x, ULL k, int p)
{
	int ret = 1 % p;
	while(k)
	{
		if(k & 1)
			ret = ret * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ret;
}
int f(int x, int p)
{
	if(x < 2)
		return x % p;
	for(int j = 2, last = 1 % p, now = 1 % p; j <= x; ++j)
		if(j == x)
			return now;
		else
		{
			last = (last + now) % p;
			swap(last, now);
		}
}
int main()
{
	for(int i = 1; i < maxc; ++i)
	{
		int k = i;
		phi[i] = i;
		for(int j = 2; j * j <= k; ++j)
			if(k % j == 0)
			{
				phi[i] -= phi[i] / j;
				while(k % j == 0)
					k /= j;
			}
		if(k > 1)
			phi[i] -= phi[i] / k;
		for(int j = 2, last = 1 % i, now = 1 % i; j; ++j)//no more than 2 * i + 2
			if(last % i == 0 && now % i == 1 % i)
			{
				mod[i] = j - 1;
				break;
			}
			else
			{
				last = (last + now) % i;
				swap(last, now);
			}
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%llu%llu%llu%d", &a, &b, &n, &c);
		printf("Case %d: %d\n", Case, pow(f(pow(a % mod[c], b, mod[c]), c), pow(f(pow(a % mod[phi[c]], b, mod[phi[c]]), phi[c]), n - 1, phi[c]) + phi[c], c));
	}
	return 0;
}
