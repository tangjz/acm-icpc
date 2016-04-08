#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int t, n, x, f[maxn], ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d", &n);
		memset(f, 0x3f, sizeof f);
		ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &x);
			x -= i;
			int k = lower_bound(f + 1, f + ans + 1, x + 1) - f;
			f[k] = x;
			if(ans < k)
				ans = k;
		}
		printf("%d\n", n - ans);
	}
	return 0;
}
