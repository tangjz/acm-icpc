/*
 * 令f[i][j]表示前i位用了j个已知碱基的方案数
 * 最大C(2000, 1000) ~ 10 ^ 600 要用高精度
 */
#include <cstdio>
const int maxn = 2001, maxl = 70, mod = 1000000000;
struct BigInt
{
	int len, num[maxl];
	void getint(const int &x) { num[len++] = x; }
	void Print()
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%9.9d", num[i]);
		putchar('\n');
	}
	void operator += (const BigInt &x)
	{
		if(len < x.len) len = x.len;
		for(int i = 0; i < len; ++i)
		{
			num[i] += x.num[i];
			if(num[i] >= mod)
			{
				num[i] -= mod;
				++num[i + 1];
			}
		}
		if(num[len]) ++len;
	}
} f[maxn];
inline bool check(char a, char b)
{
	return a == 'A' && b == 'T' || a == 'G' && b == 'C' || a == 'C' && b == 'G' || a == 'T' && b == 'A';
}
int n, m;
char s[maxn], t[maxn];
int main()
{
	scanf("%d%d%s%s", &n, &m, s, t);
	f[0].getint(1);
	for(int i = 1; i <= n; ++i)
		for(int j = m; j; --j)
			if(check(s[i - 1], t[j - 1])) f[j] += f[j - 1];
	f[m].Print();
	return 0;
}
