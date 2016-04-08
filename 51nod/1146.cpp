#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 29 + 1, maxs = 514229 + 10, maxss = 100000 + 10, mod = 1000000007;
struct Fibonacci
{
	int num1, num2;
	bool operator == (const Fibonacci &x) const
	{
		return num1 == x.num1 && num2 == x.num2;
	}
	Fibonacci operator * (const Fibonacci &x) const
	{
		return (Fibonacci){(int)(((LL)num1 * x.num1 + (LL)num2 * x.num2) % mod),
		(int)(((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % mod)};
	}
	Fibonacci pow(LL k)
	{
		Fibonacci ret = (Fibonacci){1, 0}, tmp = *this;
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
int fib[maxn], tlen, f[maxss];
LL n, ans;
char str[maxn][maxs], tmp[maxss];
int calc(int idx)
{
	int &slen = fib[idx], ret = 0;
	char *smp = str[idx];
	for(int i = 0, j = 0; i < slen; ++i)
	{
		while(j && smp[i] != tmp[j])
			j = f[j];
		if(smp[i] == tmp[j])
			++j;
		if(j == tlen)
		{
			++ret;
			j = f[j];
		}
	}
	return ret;
}
int main()
{
	fib[1] = fib[2] = 1;
	str[1][0] = 'a';
	str[2][0] = 'b';
	for(int i = 3; i < maxn; ++i)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
		strcpy(str[i], str[i - 1]);
		strcat(str[i], str[i - 2]);
	}
	scanf("%lld%s", &n, tmp);
	tlen = strlen(tmp);
	for(int i = 1, j = 0; i < tlen; ++i)
	{
		while(j && tmp[i] != tmp[j])
			j = f[j];
		if(tmp[i] == tmp[j])
			++j;
		f[i + 1] = j;
	}
	for(int i = 1, j; i < maxn; ++i)
		if(tlen >= fib[i] && tlen < fib[i + 1])
		{
			if(tlen > fib[i])
				++i;
			for(j = i; j < maxn && j <= i + 2; ++j)
				if(calc(j))
					break;
			if(tlen == 1 && tmp[0] == 'a' && n == 1) //a
				ans = 1;
			else if(j > i + 2 || n < j)
				ans = 0;
			else if(calc(j + 1) == 2) //babbabab
			{
				ans = A.pow(n - j + 3).num2 - 1;
				if(ans < 0)
					ans += mod;
			}
			else if(calc(j + 2) == 2) // b
				ans = A.pow(n - j + 1).num2;
			else //bab
			{
				ans = A.pow(n - j + 2).num2 - ((n - j + 2) & 1);
				if(ans < 0)
					ans += mod;
			}
			break;
		}
	printf("%d\n", ans);
	return 0;
}
