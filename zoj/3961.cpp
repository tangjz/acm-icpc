#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 101;
int t, n, m, x, y, ans;
pair<int, int> a[maxn], b[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &n, &m, &x, &y);
		for(int i = 0; i < x; ++i)
			scanf("%d%d", &a[i].first, &a[i].second);
		for(int i = 0; i < y; ++i)
			scanf("%d%d", &b[i].first, &b[i].second);
		ans = 0;
		for(int i = 0; i < x; ++i)
			for(int j = 0; j < y; ++j)
			{
				int L = max(a[i].first, b[j].first);
				int R = min(a[i].second, b[j].second);
				ans += max(R - L + 1 - m + 1, 0);
			}
		printf("%d\n", ans);
	}
	return 0;
}
