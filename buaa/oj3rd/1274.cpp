#include <cstdio>
typedef long long LL;
const int maxn = 200001;
int t, n, m, a[maxn], buy[maxn], sell[maxn], cnt, que[maxn][2], L, R;
LL ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i <= n; ++i)
			scanf("%d%d", buy + i, sell + i);
		for(int i = 0; i <= n; ++i)
		{
			int tmp = 0;
			for( ; L < R && que[L][0] < sell[i]; ++L)
				tmp += que[L][1];
			if(tmp)
			{
				que[--L][0] = sell[i];
				que[L][1] = tmp;
			}
			if(i == n)
			{
				for( ; L < R; ++L)
					ans -= (LL)que[L][0] * que[L][1];
				break;
			}
			tmp = i ? a[i] - a[i - 1] : m;
			for( ; L < R && que[R - 1][0] > buy[i]; --R)
			{
				ans -= (LL)que[R - 1][0] * que[R - 1][1];
				tmp += que[R - 1][1];
			}
			que[R][0] = buy[i];
			que[R++][1] = tmp;
			ans += (LL)buy[i] * tmp;
			for(tmp = a[i + 1] - a[i]; tmp; )
			{
				int val = tmp < que[L][1] ? tmp : que[L][1];
				tmp -= val;
				que[L][1] -= val;
				if(!que[L][1])
					++L;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
