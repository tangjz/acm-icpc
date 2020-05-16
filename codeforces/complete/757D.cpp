#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 77, maxv = 20, maxs = 1 << maxv | 1, maxd = 7, mod = 1000000007;
int n, lim, all, f[maxn][maxs], ans;
pair<int, int> g[maxn][maxd];
char str[maxn];
int main()
{
	scanf("%d%s", &n, str + 1);
	lim = maxv;
	all = (1 << lim) - 1;
	for(int i = 0; i < n; ++i)
	{
		int val = 0;
		for(int j = 1; i + j <= n; ++j)
		{
			val = (val << 1) + (str[i + j] - '0');
			if(val > lim)
				break;
			if(val)
				g[i][++g[i][0].first] = make_pair(i + j, 1 << (val - 1));
		}
	}
	for(int i = 0; i <= n; ++i)
	{
		f[i][0] = 1;
		for(int j = 0; j <= all; ++j)
		{
			if(!f[i][j])
				continue;
			for(int k = 1; k <= g[i][0].first; ++k)
			{
				int ii = g[i][k].first, jj = j | g[i][k].second;
				if((f[ii][jj] += f[i][j]) >= mod)
					f[ii][jj] -= mod;
			}
		}
		for(int j = 1, k = 0; j <= all; j |= 1 << ++k)
			if((ans += f[i][j]) >= mod)
				ans -= mod;
	}
	printf("%d\n", ans);
	return 0;
}
