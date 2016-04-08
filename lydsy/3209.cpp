/*
 * 从左到右考虑n的二进制表示，遇到1，
 * 若选，则到下一次遇到1再考虑，到下一次1之前的1个数为sum
 * 若不选，则后面可以随意填1，方案数为∏(sum+i)*C(len,i)
 */
#include <cstdio>
const int maxlen = 55, mod = 10000007;
typedef long long LL;
int len, p[maxlen][maxlen], cnt, ans = 1;
LL n, c[maxlen][maxlen];
bool flag[maxlen];
int pow(int x, LL k)
{
	if(!x) return 1;
	int ret = 1;
	for(int t = 0; k; k >>= 1, ++t)
		if(k & 1) ret = ret * (LL)p[x][t] % mod;
	return ret;
}
int main()
{
	scanf("%lld", &n);
	while(n)
	{
		flag[++len] = n & 1;
		n >>= 1;
	}
	for(int i = 0; i < len; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	for(int i = 1; i < len; ++i)
	{
		p[i][0] = i;
		for(int j = 1; j < maxlen; ++j)
			p[i][j] = (LL)p[i][j - 1] * p[i][j - 1] % mod;
	}
	for(int i = len; i; --i)
		if(flag[i])
		{
			for(int j = 0; j < i; ++j)
				ans = ans * (LL)pow(cnt + j, c[i - 1][j]) % mod;
			++cnt;
		}
	printf("%lld\n", ans * (LL)cnt % mod);
	return 0;
}
