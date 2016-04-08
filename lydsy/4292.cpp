#include <cstdio>
typedef long long LL;
const int maxf = 1458;
const LL INF = (LL)1e18;
int ans;
LL k, a, b;
int calc(LL x)
{
	int ret = 0;
	for( ; x; x /= 10)
		ret += (x % 10) * (x % 10);
	return ret;
}
int main()
{
	scanf("%lld%lld%lld", &k, &a, &b);
	for(int i = 1; i <= maxf && i <= INF / k; ++i)
		if(calc(i * k) == i && a <= i * k && i * k <= b)
			++ans;
	printf("%d\n", ans);
	return 0;
}
