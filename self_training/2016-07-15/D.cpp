#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxs = 1001, maxc = 26;
int tot, nxt[maxn][maxc];
int n, m, cur, sum[2], cnt[2][maxc];
long long ans;
char str[maxs];
void insert()
{
	int rt = 0;
	for(int i = 0; str[i]; ++i)
	{
		str[i] -= 'a';
		if(!nxt[rt][str[i]])
		{
			nxt[rt][str[i]] = tot;
			memset(nxt + (tot++), 0, sizeof nxt[0]);
		}
		rt = nxt[rt][str[i]];
	}
}
void query()
{
	for(int i = 0; i < maxc; ++i)
		if(nxt[0][i])
			++sum[cur];
	for(int u = 1; u < tot; ++u)
		for(int i = 0; i < maxc; ++i)
			if(nxt[u][i])
			{
				++sum[cur];
				++cnt[cur][i];
			}
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		tot = 0;
		memset(nxt + (tot++), 0, sizeof nxt[0]);
		while(n--)
		{
			scanf("%s", str);
			insert();
		}
		sum[cur = 0] = 0;
		memset(cnt + cur, 0, sizeof cnt[0]);
		query();
		tot = 0;
		memset(nxt + (tot++), 0, sizeof nxt[0]);
		while(m--)
		{
			scanf("%s", str);
			std::reverse(str, str + strlen(str));
			insert();
		}
		sum[cur = 1] = 0;
		memset(cnt + cur, 0, sizeof cnt[0]);
		query();
		ans = (long long)sum[0] * sum[1];
		for(int i = 0; i < maxc; ++i)
			ans -= (long long)cnt[0][i] * cnt[1][i];
		printf("%lld\n", ans);
	}
	return 0;
}
