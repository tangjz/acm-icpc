#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 29, maxs = 514229 + 10, maxss = 100000 + 10;
struct Fibonacci
{
	LL num1, num2;
	bool operator == (const Fibonacci &x) const
	{
		return num1 == x.num1 && num2 == x.num2;
	}
	Fibonacci operator * (const Fibonacci &x) const
	{
		return (Fibonacci){num1 * x.num1 + num2 * x.num2, num1 * x.num2 + num2 * (x.num1 + x.num2)};
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
int fib[maxn], m, tlen, f[maxss];
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
	fib[0] = fib[1] = 1;
	str[0][0] = '0';
	str[1][0] = '1';
	for(int i = 2; i < maxn; ++i)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
		strcpy(str[i], str[i - 1]);
		strcat(str[i], str[i - 2]);
	}
	for(int Case = 1; scanf("%I64d%s", &n, tmp) == 2; ++Case)
	{
		tlen = strlen(tmp);
		for(int i = 1, j = 0; i < tlen; ++i)
		{
			while(j && tmp[i] != tmp[j])
				j = f[j];
			if(tmp[i] == tmp[j])
				++j;
			f[i + 1] = j;
		}
		for(int i = 0; i < maxn; ++i)
			if(tlen >= fib[i] && tlen < fib[i + 1])
			{
				int j;
				for(j = i; j < maxn && j <= i + 3; ++j)
					if(calc(j))
						break;
				if(tlen == 1 && tmp[0] == '0' && n == 0) //0
					ans = 1;
				else if(j > i + 3 || n < j)
					ans = 0;
				else if(calc(j + 1) == 2) //10110101
					ans = A.pow(n - j + 3).num2 - 1;
				else if(calc(j + 2) == 2) //1
					ans = A.pow(n - j + 1).num2;
				else //101
					ans = A.pow(n - j + 2).num2 - ((n - j + 2) & 1);
				break;
			}
		printf("Case %d: %I64d\n", Case, ans);
	}
	return 0;
}
