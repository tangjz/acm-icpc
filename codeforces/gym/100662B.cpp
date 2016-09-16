#include <cstdio>
#include <cstring>
const int maxn = 1010;
int t, n, a[maxn], ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		ans = (int)(~0u >> 1);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= 1000; ++i)
		{
			int cnt = 0;
			for(int j = 0; j < n; ++j)
				cnt += (a[j] - 1) / i;
			if(ans > cnt + i)
				ans = cnt + i;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
