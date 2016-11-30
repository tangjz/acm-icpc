#include <cmath>
#include <stdio.h> 
typedef long long LL;
const int maxn = 10000001;
int f[maxn], g[maxn];
inline int Sqrt(LL n)
{
	int ret = (int)sqrt(n);
	for( ; (LL)ret * ret > n; --ret);
	for( ; (ret + 1LL) * (ret + 1LL) <= n; ++ret);
	return ret;
}
inline LL calc(LL n)
{
	if(n < maxn)
		return f[(int)n];
	static LL his_n = -1, ret, tmp;
	if(his_n == n)
		return ret;
	his_n = n;
	ret = 0;
	for(int i = 1; (tmp = (LL)i * i) <= n; ++i)
		ret += Sqrt(n - tmp) + 1;
	return ret;
}
int main()
{
	for(int i = 1, idx; (idx = i * i) < maxn; ++i)
		for(int j = 0, jdx; (jdx = idx + j * j) < maxn; ++j)
			++f[jdx];
	g[1] = 1;
	for(int i = 1; i < maxn; ++i)
		for(int j = i + i, k = 2; j < maxn; j += i, ++k)
			g[j] -= g[i] * f[k];
	for(int i = 1; i < maxn; ++i)
		f[i] += f[i - 1];
	for(LL n; scanf("%lld", &n) == 1; )
	{
		LL ans = 0, tmp;
		for(int i = 1; (tmp = (LL)i * i) <= n; ++i)
			if(g[i])
				ans += g[i] * calc(n / tmp);
		printf("%lld\n", ans);
	}
	return 0;
}
