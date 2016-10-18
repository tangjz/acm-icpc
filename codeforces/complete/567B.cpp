#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010;
int n, k, a[maxn], tot, que[maxn];
long long f[maxn][3], g[maxn][3], ans;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i), que[tot++] = a[i];
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j < 3; ++j)
		{
			if(a[i] % k != 0)
				continue;
			int pos = lower_bound(que, que + tot, a[i] / k) - que;
			if(que[pos] != a[i] / k)
				continue;
			f[i][j] = g[pos][j - 1];
		}
		f[i][0] = 1;
		int pos = lower_bound(que, que + tot, a[i]) - que;
		for(int j = 0; j < 3; ++j)
		{
			g[pos][j] += f[i][j];
			//printf("%d%c", f[i][j], " \n"[j == 2]);
		}//puts("");
		ans += f[i][2];
	}
	printf("%I64d\n", ans);
	return 0;
}
