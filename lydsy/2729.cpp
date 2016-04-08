/*
 * 女生不相邻 (n + 2)! * C(n + 3, m) * m!
 * 女生不相邻老师相邻 2 * (n + 1)! * C(n + 2, m) * m!
 */
#include <cstdio>
const int maxn = 2000, mod = 1000000;
struct Big_int
{
	int len, num[maxn];
	void getint(const int &x)
	{
		num[0] = x;
		len = 1;
		if(num[0] >= mod)
		{
			num[1] = num[0] / mod;
			num[0] %= mod;
			while(num[len])
			{
				num[len + 1] = num[len] / mod;
				num[len++] %= mod;
			}
		}
	}
	void put(void) const
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i) printf("%6.6d", num[i]);
		putchar('\n');
	}
	Big_int operator - (const Big_int &x) const
	{
		Big_int tmp = *this;
		for(int i = 0; i < len; ++i)
		{
			if(tmp.num[i] < x.num[i])
			{
				tmp.num[i] += mod;
				--tmp.num[i + 1];
			}
			tmp.num[i] -= x.num[i];
		}
		while(!tmp.num[tmp.len - 1] && tmp.len > 1) --tmp.len;
		return tmp;
	}
	Big_int operator -= (const Big_int &x) { return *this = *this - x; }
	Big_int operator * (int x) const
	{
		Big_int tmp = *this;
		for(int i = 0; i < len; ++i) tmp.num[i] *= x;
		for(int i = 0; i < len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		while(tmp.num[tmp.len])
		{
			if(tmp.num[tmp.len] >= mod)
			{
				tmp.num[tmp.len + 1] = tmp.num[tmp.len] / mod;
				tmp.num[tmp.len] %= mod;
			}
			++tmp.len;
		}
		return tmp;
	}
	Big_int operator *= (const int &x) { return *this = *this * x; }
} A;
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	A.getint(1);
	for(int i = 2; i <= n + 1; ++i) A *= i;
	for(int i = n - m + 4; i <= n + 2; ++i) A *= i;
	((A * (n + 2)) * (n + 3) - (A * (n - m + 3)) * 2).put();
	return 0;
}
