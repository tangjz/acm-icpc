#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010, INF = 0x3f3f3f3f;
int n, a[maxn];
long long ans[maxn];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		a[0] = a[n + 1] = INF;
		memset(ans + 1, 0, n * sizeof(long long));
		for(int i = 1; i <= n; ++i)
		{
			int L = i, R = i, val = a[i];
			while(1)
			{
				for( ; a[L - 1] <= a[i] && a[L - 1] >= val; --L);
				for( ; a[R + 1] <= a[i] && a[R + 1] >= val; ++R);
				ans[R - L + 1] = max(ans[R - L + 1], (long long)a[i] * val);
				if(a[L - 1] > a[i] && a[R + 1] > a[i])
					break;
				if(a[R + 1] > a[i] || a[L - 1] <= a[i] && a[L - 1] > a[R + 1])
				{
					--L;
					val = min(val, a[L]);
				}
				else
				{
					++R;
					val = min(val, a[R]);
				}
			}
		}
		for(int i = n - 1; i >= 1; --i)
			ans[i] = max(ans[i], ans[i + 1]);
		for(int i = 1; i <= n; ++i)
			printf("%I64d\n", ans[i]);
	}
	return 0;
}
