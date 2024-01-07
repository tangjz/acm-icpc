#include <cmath>
#include <cstdio>
#include <algorithm>
const int maxn = 100001;
int t, n, c, q, v[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &c);
		for(int i = 0; i < n; ++i)
			scanf("%d%*d%*d", v + i);
		std::sort(v, v + n);
		scanf("%d", &q);
		while(q--)
		{
			int t, k;
			scanf("%d%d", &t, &k);
			long long val = 2LL * c * t + (long long)v[k - 1] * v[k - 1];
			double ans = sqrt(val);
			printf("%.3f\n", ans);
		}
	}
	return 0;
}
