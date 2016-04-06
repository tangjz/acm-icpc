#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int main()
{
	int m;
	LL n, now = 1;
	scanf("%lld%d", &n, &m);
	if(m == 1)
	{
		printf("%lld\n", n);
		return 0;
	}
	for(LL i = 1; i <= n; ++i)
	{
		if(now + m < i)
		{
			LL delta = min(n - i, (i - now + 1) / (m - 1) - 1);
			now += m * delta;
			i += delta;
		}
		now = (now + m - 1) % i + 1;
	}
	printf("%lld\n", now);
	return 0;
}
