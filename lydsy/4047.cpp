#include <cstdio>
#include <algorithm>
#include <functional>
const int maxn = 150001, maxm = 9, INF = 0x3f3f3f3f;
int t, n, m, f[maxm][maxn];
std::pair<int, int> a[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", &a[i].first, &a[i].second);
		sort(a + 1, a + n + 1, std::greater<std::pair<int, int> >());
		for(int i = 0; i <= m; ++i)
		{
			f[i][0] = -INF;
			for(int j = 1; j <= n; ++j)
			{
				int val = a[j].first;
				if(i && val > f[i - 1][j - 1])
					val = f[i - 1][j - 1];
				f[i][j] = std::max(f[i][j - 1], val - a[j].second);
			}
		}
		printf("%d\n", std::max(f[m][n], 0));
	}
	return 0;
}
