#include <cstdio>
#include <algorithm>
const int maxn = 100001, maxm = 321;
int n, q, sqn, a[maxn];
std::pair<int, int> f[maxm][maxn];
int main()
{
	scanf("%d", &n);
	for(sqn = 1; sqn * sqn <= n; ++sqn);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i < sqn; ++i)
		for(int j = n; j >= 1; --j)
		{
			int k = j + a[j] + i;
			if(k > n)
				f[i][j] = std::make_pair(k, 1);
			else
				f[i][j] = std::make_pair(f[i][k].first, f[i][k].second + 1);
		}
	scanf("%d", &q);
	while(q--)
	{
		int u, w, ans = 0;
		scanf("%d%d", &u, &w);
		if(w < sqn)
			ans = f[w][u].second;
		else
			for( ; u <= n; u += a[u] + w, ++ans);
		printf("%d\n", ans);
	}
	return 0;
}
