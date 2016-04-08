#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 2002, INF = ~0u >> 1;
int n, f[maxn][maxn];
pair<int, int> p[maxn];
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i <= n; ++i)
		f[0][i] = f[i][n + 1] = -INF;
	f[0][1] = 0;
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &p[i].first, &p[i].second);
	sort(p, p + n, greater<pair<int, int> >());
	for(int t = 1; t <= n; ++t)
	{
		int &a = p[t - 1].first, &b = p[t - 1].second;
		--a;
		for(int i = 0; i <= n; ++i)
		{
			int j = i - a > 1 ? i - a : 1;
			f[t][i] = f[t - 1][i];
			if(f[t - 1][j] != -INF)
				upd(f[t][i], f[t - 1][j] + b);
		}
	}
	for(int i = 1; i <= n; ++i)
		upd(f[n][0], f[n][i]);
	printf("%d\n", f[n][0]);
	return 0;
}
