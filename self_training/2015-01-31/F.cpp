#include <cstdio>
#include <cstring>
const int maxn = 4000010;
int n, m, k, cnt[maxn], sum[maxn];
int main()
{
	while(scanf("%d%d%d", &n, &m, &k) == 3)
	{
		int ans = 0, tmp, hmax = 0;
		memset(cnt, 0, sizeof cnt);
		memset(sum, 0, sizeof sum);
		for(int i = 0, x; i < n; ++i)
		{
			scanf("%d", &x);
			if(!cnt[x])
				sum[x] = 1;
			++cnt[x];
			if(hmax < x)
				hmax = x;
		}
		for(int i = 1; i <= hmax + k; ++i)
			sum[i] += sum[i - 1];
		for(int i = 1; i <= hmax; ++i)
		{
			tmp = sum[i + k - 1] - sum[i - 1];
			if(cnt[i + k - 1] > m - k)
				tmp += m - k;
			else if(cnt[i + k - 1] > 0)
				tmp += cnt[i + k - 1] - 1;
			if(ans < tmp)
				ans = tmp;
		}
		printf("%d\n", ans);
	}
	return 0;
}
