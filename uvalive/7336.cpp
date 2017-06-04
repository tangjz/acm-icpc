#include <stdio.h>
#include <cstring>
typedef long long LL;
int t, n, cnt[10][2][2];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(cnt, 0, sizeof cnt);
		scanf("%d", &n);
		while(n--)
		{
			int d, x;
			char y;
			scanf("%d %d %c", &d, &x, &y);
			++cnt[d - 1][x][y == 'c'];
		}
		LL ans = 0;
		for(int i = 0; i < 10; ++i)
			for(int j = i + 1; j < 10; ++j)
				ans += (LL)cnt[i][0][0] * cnt[j][1][1];
		printf("%lld\n", ans);
	}
	return 0;
}
