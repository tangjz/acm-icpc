#include <cstdio>
int n, a[1001], cnt[1001][2], ans[2];
int main()
{
	int i, j;
	while(scanf("%d", &a[n + 1]) != EOF) ++n;
	for(a[0] = 30001, i = 1; i <= n; ++i)
		for(j = 0; j < i; ++j)
			if(a[i] <= a[j] && cnt[i][0] < cnt[j][0] + 1) cnt[i][0] = cnt[j][0] + 1;
	for(a[0] = 0, i = 1; i <= n; ++i)
		for(j = 0; j < i; ++j)
			if(a[i] > a[j] && cnt[i][1] < cnt[j][1] + 1) cnt[i][1] = cnt[j][1] + 1;
	for(ans[0] = cnt[1][0], ans[1] = cnt[1][1], i = 2; i <= n; ++i)
	{
		if(cnt[i][0] > ans[0]) ans[0] = cnt[i][0];
		if(cnt[i][1] > ans[1]) ans[1] = cnt[i][1];
	}
	printf("%d\n%d\n", ans[0], ans[1]);
}
