#include <cstdio>
#include <cstring>
const int maxn = 1048576, maxk = 11;
int t, n, q;
long long cnt[maxk];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(cnt, 0, sizeof cnt);
		scanf("%d%d", &n, &q);
		while(q--)
		{
			int x, y;
			char op[10];
			scanf("%s%d%d", op, &x, &y);
			if(op[0] == 'P')
				cnt[x] += y;
			else
			{
				long long ans = 0;
				for(int i = 1; i < maxk; ++i)
					ans += cnt[i] * (y / i - (x - 1) / i);
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
