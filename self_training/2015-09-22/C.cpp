#include <cstdio>
typedef long long LL;
const int maxt = 54;
LL calc(LL lim)
{
	LL ret = 0, cnt = 0;
	for(LL i = maxt; i >= 0; --i)
		if(lim & (1LL << i))
		{
			ret += cnt * (1LL << i);
			if(i)
				ret += i * (1LL << i - 1);
			++cnt;
		}
	return ret;
}
int main()
{
	LL a, b;
	while(scanf("%lld%lld", &a, &b) == 2)
		printf("%lld\n", calc(b + 1) - calc(a));
	return 0;
}
