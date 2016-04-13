#include <stdio.h>
inline void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
}
const int maxn = 1000001, maxm = 1001, maxl = 2000;
int t, n, m, a[maxl], b[maxl], fact[maxn][3], Gcd[maxm][maxm];
int tot, prime[maxn / 10];
unsigned int ans;
inline int gcd(int x, int y)
{
	if(!x || !y)
		return x | y;
	if(x < maxm)
		return Gcd[y % x][x];
	if(y < maxm)
		return Gcd[x % y][y];
	register int ret = 1, i, tmp;
	for(i = 0; i < 3; ++i)
	{
		tmp = fact[x][i];
		if(tmp == 1)
			continue;
		if(tmp < maxm)
		{
			tmp = Gcd[y % tmp][tmp];
			ret *= tmp;
			y /= tmp;
		}
		else if(y % tmp == 0)
		{
			ret *= tmp;
			y /= tmp;
		}
	}
	return ret;
}
int main()
{
	register int i, j, o;
	for(i = 1; i < maxm; ++i)
		Gcd[0][i] = i;
	for(i = 1; i < maxm; ++i)
		for(j = i; j < maxm; ++j)
			Gcd[i][j] = j - i < i ? Gcd[j - i][i] : Gcd[i][j - i];
	fact[1][0] = fact[1][1] = fact[1][2] = 1;
	for(i = 2; i < maxn; ++i)
	{
		if(!fact[i][0])
		{
			prime[tot++] = fact[i][0] = i;
			fact[i][1] = fact[i][2] = 1;
		}
		for(j = 0; j < tot && (o = i * prime[j]) < maxn; ++j)
		{
			fact[o][0] = fact[i][0];
			fact[o][1] = fact[i][1];
			fact[o][2] = fact[i][2];
			if(fact[o][0] * prime[j] < maxm)
				fact[o][0] *= prime[j];
			else if(fact[o][1] * prime[j] < maxm)
				fact[o][1] *= prime[j];
			else
				fact[o][2] *= prime[j];
			if(i % prime[j] == 0)
				break;
		}
	}
	scan(t);
	while(t--)
	{
		ans = 0;
		scan(n);
		scan(m);
		for(i = 0; i < n; ++i)
			scan(a[i]);
		for(i = 0; i < m; ++i)
			scan(b[i]);
		for(i = 0; i < n; ++i)
			for(j = 0; j < m; ++j)
				ans += gcd(a[i], b[j]) ^ i ^ j;
		printf("%u\n", ans);
	}
	return 0;
}
