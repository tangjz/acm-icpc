/*
 * °´ÕÕi - x,xÅÅ¸öĞò ÇóLIS 
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, tot, g[100001], ans;
pair<int, int> num[100001];
int main()
{
	int i = 0, x;
	scanf("%d", &n);
	for(i = 1; i <= n; ++i)
	{
		scanf("%d", &x);
		if(x <= i) num[tot++] = make_pair(i - x, x);
	}
	sort(num, num + tot);
	memset(g, 0x3f, sizeof(g));
	for(i = 0; i < tot; ++i)
	{
		x = lower_bound(g + 1, g + tot, num[i].second) - g;
		g[x] = num[i].second;
		ans = max(ans, x);
	}
	printf("%d\n", ans);
	return 0;
}
