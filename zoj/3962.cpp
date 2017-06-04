#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxl = 9, maxd = 16, EC[maxd | 1] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6, 6, 5, 4, 5, 5, 4};
int t;
LL pw[maxl], f[maxl], g[maxd | 1];
LL solve(LL n)
{
	if(n < 0) // n == -1
		return 0;
	if(n >= pw[maxl - 1])
	{
		LL ret = solve(n - pw[maxl - 1]) + f[maxl - 1] * g[maxd - 1];
		return ret;
	} // n <= FFFFFFFF
	char buf[maxl];
	int len = sprintf(buf, "%08llX", n);
	for(int i = 0; i < len; ++i)
		buf[i] = buf[i] >= '0' && buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'A' + 10;
	LL ret = 0, prec = 0;
	for(int i = 0; i < len; prec += EC[buf[i++]])
	{
		if(buf[i] > 0) // <
		{
			ret += (prec * buf[i] + g[buf[i] - 1]) * pw[len - 1 - i];
			ret += buf[i] * f[len - 1 - i] * g[maxd - 1];
		} // =
		ret += EC[buf[i]];
	}
	return ret;
}
int main()
{
	pw[0] = 1;
	for(int i = 1; i < maxl; ++i)
	{
		pw[i] = pw[i - 1] << 4;
		f[i] = i * pw[i - 1];
	}
	for(int i = 0; i < maxd; ++i)
		g[i] = (i ? g[i - 1] : 0) + EC[i];
	scanf("%d", &t);
	while(t--)
	{
		LL n, m;
		scanf("%lld%llX", &n, &m);
		printf("%lld\n", solve(n + m - 1) - solve(m - 1));
	}
	return 0;
}
