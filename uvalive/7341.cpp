#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 251;
int t, n, m, q, h, a[maxn][maxn], s[maxn][maxn], b[maxn], ord[maxn];
int val[maxn], cnt[1 << 8], tmp[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				scanf("%d", a[i] + j);
		if(n > m)
		{
			for(int i = 1; i <= n; ++i)
				for(int j = i + 1; j <= n; ++j)
					swap(a[i][j], a[j][i]);
			swap(n, m);
		}
		printf("Case %d:\n", Case);
		scanf("%d", &q);
		while(q--)
		{
			int ans = 0;
			scanf("%d", &h);
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= m; ++j)
					s[i][j] = s[i - 1][j] + (a[i][j] < h ? -1 : 1);
			for(int len = n; len >= 1 && ans < m * len; --len)
			{
				int all = 1, bit = 0;
				for( ; all * all <= m * len; all <<= 1, ++bit);
				--all;
				for(int L = 0, R = len; R <= n && ans < m * len; ++L, ++R)
				{
					int mx = 0, pr = m + 1, dt = 0;
					bool flag = 0;
					for(int i = 1; i <= m; ++i)
					{
						int v = s[R][i] - s[L][i];
						flag |= v >= 0;
						b[i] = b[i - 1] + v;
						if(dt > b[i])
							dt = b[i];
					}
					if(!flag)
						continue;
					memset(cnt, 0, (all + 1) * sizeof(int));
					for(int i = 0; i <= m; ++i)
					{
						val[i] = b[i] - dt;
						++cnt[val[i] & all];
					}
					for(int i = 1; i <= all; ++i)
						cnt[i] += cnt[i - 1];
					for(int i = m; i >= 0; --i)
						tmp[--cnt[val[i] & all]] = i;
					memset(cnt, 0, (all + 1) * sizeof(int));
					for(int i = 0; i <= m; ++i)
						++cnt[val[i] >> bit];
					for(int i = 1; i <= all; ++i)
						cnt[i] += cnt[i - 1];
					for(int i = m; i >= 0; --i)
						ord[--cnt[val[tmp[i]] >> bit]] = tmp[i];
					for(int i = 0; i <= m; ++i)
					{
						if(pr < ord[i] && mx < ord[i] - pr)
							mx = ord[i] - pr;
						if(pr > ord[i])
							pr = ord[i];
					}
					if(ans < mx * len)
						ans = mx * len;
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
