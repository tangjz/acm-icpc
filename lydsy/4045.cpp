#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 100001;
const char *color = "BW";
int t, n, cnt[2], seq[maxn][2], sum[2], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		cnt[0] = cnt[1] = 0;
		for(int i = 1; i <= n; ++i)
		{
			int typ, val;
			char op[2];
			scanf("%d%s", &val, op);
			typ = seq[i][0] = op[0] == color[1];
			cnt[typ] += seq[i][1] = val;
		}
		if(!cnt[0] || !cnt[1])
		{
			printf("%d\n", cnt[0] + cnt[1]);
			continue;
		}
		int r = std::__gcd(cnt[0], cnt[1]);
		cnt[0] /= r;
		cnt[1] /= r;
		ans = sum[0] = sum[1] = 0;
		for(int i = 1; i <= n; ++i)
		{
			int typ = seq[i][0], val = seq[i][1];
			if(sum[!typ] && sum[!typ] % cnt[!typ] == 0)
			{
				LL tmp = sum[!typ] / cnt[!typ] * cnt[typ];
				if(sum[typ] < tmp && tmp <= sum[typ] + val)
				{
					++ans;
					sum[!typ] = 0;
					sum[typ] -= tmp;
				}
			}
			sum[typ] += val;
		}
		if(sum[0] && sum[1])
			++ans;
		printf("%d\n", ans);
	}
	return 0;
}
