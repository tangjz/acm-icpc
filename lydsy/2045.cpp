/*
 * 不想反演可以直接用容斥 反演同1101
 * 令f[i]表示gcd(x,y)=i的有序对数 
 * f[i] = [n / i] * [m / i] - f[i * 2] - f[i * 3]... 
 */
#include <cstdio>
typedef long long LL;
const int maxn = 1000001;
int n, m, d, lim;
LL f[maxn], ans;
int main()
{
	scanf("%d%d%d", &n, &m, &d);
	lim = n < m ? n : m;
	for(int i = lim; i >= d; --i)
	{
		f[i] = (LL)(n / i) * (m / i);
		for(int j = i << 1; j <= lim; j += i)
			f[i] -= f[j];
	}
	printf("%lld\n", f[d]);
	return 0;
}
