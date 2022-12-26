/*
 * 不想写线性筛可以直接用容斥
 * 令f[i]表示gcd(x,y)=i的有序对数
 * f[i] = [n / i] * [m / i] - f[i * 2] - f[i * 3]...
 * 题目的k就是gcd(x, y) - 1
 */
#include <cstdio>
typedef long long LL;
const int maxn = 100001;
int n, m, lim;
LL f[maxn], ans;
int main()
{
	scanf("%d%d", &n, &m);
	lim = n < m ? n : m;
	for(int i = lim; i; --i)
	{
		f[i] = (LL)(n / i) * (m / i);
		for(int j = i << 1; j <= lim; j += i)
			f[i] -= f[j];
		ans += f[i] * (i << 1) - f[i];
	}
	printf("%lld\n", ans);
	return 0;
}
