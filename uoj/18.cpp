#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 20, maxm = 129;
int d, n, cnt[maxm][maxm], ans1, ans2;
int main()
{
	scanf("%d%d", &d, &n);
	for(int i = 0; i < n; ++i)
	{
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		for(int j = max(x - d, 0), k = min(x + d, maxm - 1); j <= k; ++j)
			for(int p = max(y - d, 0), q = min(y + d, maxm - 1); p <= q; ++p)
				cnt[j][p] += w;
	}
	for(int i = 0; i < maxm; ++i)
		for(int j = 0; j < maxm; ++j)
			if(ans1 < cnt[i][j])
			{
				ans1 = cnt[i][j];
				ans2 = 1;
			}
			else if(ans1 == cnt[i][j])
				++ans2;
	printf("%d %d\n", ans2, ans1);
	return 0;
}
