#include <cstdio>
#include <cstring>
const int maxn = 100001, maxd = 256;
int n, cnt[maxd], tot, ans;
char str[maxn];
int main()
{
	scanf("%d%s", &n, str);
	for(int i = 0; i < n; ++i)
	{
		if(!cnt[str[i]])
			++tot;
		++cnt[str[i]];
	}
	ans = n;
	memset(cnt, 0, sizeof cnt);
	for(int i = 0, j = 0, cur = 0; i < n; )
	{
		for( ; cur < tot && j < n; ++j)
		{
			if(!cnt[str[j]])
				++cur;
			++cnt[str[j]];
		}
		if(cur < tot)
			break;
		for( ; cur == tot && i < n; ++i)
		{
			if(ans > j - i)
				ans = j - i;
			--cnt[str[i]];
			if(!cnt[str[i]])
				--cur;
		}
	}
	printf("%d\n", ans);
	return 0;
}
