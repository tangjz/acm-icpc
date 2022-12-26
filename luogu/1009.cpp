#include <cstdio>
const int maxn = 10, mod = 10000000;
struct Big_int
{
	int len, num[maxn];
	void operator += (const Big_int &x)
	{
		for(int i = 0; i < x.len; ++i)
		{
			num[i] += x.num[i];
			if(num[i] >= mod) num[i] -= mod, ++num[i + 1];
		}
		for(int i = x.len; i < len; ++i)
			if(num[i] >= mod) num[i] -= mod, ++num[i + 1];
		while(num[len])
		{
			if(num[len] >= mod) num[len] -= mod, ++num[len + 1];
			++len;
		}
	}
	void operator *= (const int &x)
	{
		for(int i = 0; i < len; ++i) num[i] *= x;
		for(int i = 0; i < len; ++i)
			if(num[i] >= mod) num[i + 1] += num[i] / mod, num[i] %= mod;
		while(num[len])
		{
			if(num[len] >= mod) num[len + 1] += num[len] / mod, num[len] %= mod;
			++len;
		}
	}
	void put()
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i) printf("%7.7d", num[i]);
		putchar('\n');
	}
} s, t;
int n;
int main()
{
	scanf("%d", &n);
	s.len = s.num[0] = t.len = t.num[0] = 1;
	for(int i = 2; i <= n; ++i) t *= i, s += t;
	s.put();
}
