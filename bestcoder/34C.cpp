#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 50010;
int n, bit1[maxn], d[maxn * 3], pos;
long long w, h, bit2[maxn], sum[maxn * 3], ans;
void add(int x, int val1, long long val2)
{
	for( ; x < maxn; x += x & -x)
	{
		bit1[x] += val1;
		bit2[x] += val2;
	}
}
pair<int, long long> query(int x)
{
	int cnt = 0;
	long long ret = 0;
	for( ; x > 0; x -= x & -x)
	{
		cnt += bit1[x];
		ret += bit2[x];
	}
	return make_pair(cnt, ret);
}
void scan(int &x)
{
	int ch = 0;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
int main()
{
	while(scanf("%d%I64d%I64d", &n, &w, &h) == 3)
	{
		ans = 1e12, pos = h;
		memset(d, 0, sizeof d);
		memset(bit1, 0, sizeof bit1);
		memset(bit2, 0, sizeof bit2);
		for(int i = 0; i < n; ++i)
			scan(d[w + i]);
		for(int i = 0; i < w + w + n; ++i)
			sum[i + 1] = sum[i] + d[i];
		if(sum[w + w + n] < w * h)
		{
			puts("-1");
			continue;
		}
		for(int i = 0, j = 0; i < w + n; ++i)
		{
			while(j < w + i)
			{
				add(d[j] + 1, 1, d[j]);
				++j;
			}
			long long hh = (sum[j] - sum[i]) / w;
			for(long long hhh = hh; hhh <= hh + 1; ++hhh)
				if(hhh >= h && sum[w + w + n] >= w * hhh)
				{
					pair<int, long long> res = query(hhh + 1);
					long long cnt = max(res.first * hhh - res.second, (sum[i + w] - sum[i] - res.second) - (w - res.first) * hhh);
					if(ans > cnt)
					{
						ans = cnt;
						pos = hhh;
					}
					else if(ans == cnt && pos < hhh)
						pos = hhh;
				}
			{
				pair<int, long long> res = query(h + 1);
				long long cnt = max(res.first * h - res.second, (sum[i + w] - sum[i] - res.second) - (w - res.first) * h);
				if(ans > cnt)
				{
					ans = cnt;
					pos = h;
				}
				else if(ans == cnt && pos < h)
					pos = h;
			}
			add(d[i] + 1, -1, -d[i]);
		}
		printf("%d %I64d\n", pos, ans);
	}
	return 0;
}
