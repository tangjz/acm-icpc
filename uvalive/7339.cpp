#include <stdio.h>
#include <cstring>
const int maxn = 100010, maxd = 26;
int t, cnt[maxd];
char str[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		memset(cnt, 0, sizeof cnt);
		scanf("%s", str);
		for(int i = 0; str[i]; ++i)
			++cnt[str[i] - 'a'];
		int mx = maxn;
		for(int i = 0; i < maxd; ++i)
			if(mx > cnt[i])
				mx = cnt[i];
		printf("Case %d: %d\n", Case, mx);
	}
	return 0;
}
