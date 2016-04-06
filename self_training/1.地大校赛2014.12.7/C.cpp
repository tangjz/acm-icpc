#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL n, m, k, ans;
int main()
{
	while(scanf("%lld%lld%lld", &n, &m, &k) == 3)
	{
		if(k > n + m - 2)
		{
			puts("fz is so clever");
			continue;
		}
		if(n < m)
			swap(n, m);
		if(k > n - 1)
			ans = m / (k - n + 2);
		else
			ans = max(n / (k + 1) * m, m / (k + 1) * n);
		printf("%lld\n", ans);
	}
	return 0;
}
