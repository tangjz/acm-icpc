#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 7, maxm = 101, maxs = 243;
int n, m, p, all, f[2][maxm][maxs], pre = 1, cur;
int seq[maxn], dis[2][maxn], ans[maxn + maxm - 1];
vector<int> tr[maxs][maxn];
inline void mod_inc(int &x, int y)
{
	(x += y) >= p && (x -= p);
}
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	// start mask
	for(int i = 0; i < 1 << n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			seq[j] = (i >> j) & 1;
			dis[0][j] = (j ? dis[0][j - 1] : 0) + seq[j];
		}
		int lowv = dis[0][0], mask = 0;
		for(int j = n - 1; j > 0; --j)
			mask = mask * 3 + (dis[0][j] - dis[0][j - 1] + 1);
		mod_inc(f[cur][lowv][mask], 1);
	}
	// trans mask
	all = 1;
	for(int i = 1; i < n; ++i)
		all *= 3;
	for(int pmsk = 0; pmsk < all; ++pmsk)
	{
		dis[0][0] = 0;
		for(int i = 1, tp = pmsk; i < n; ++i, tp /= 3)
			dis[0][i] = dis[0][i - 1] + (tp % 3 - 1);
		for(int i = 0; i < 1 << n; ++i)
		{
			for(int j = 0; j < n; ++j)
				seq[j] = (i >> j) & 1;
			dis[1][0] = dis[0][0] + seq[0];
			for(int j = 1; j < n; ++j)
				dis[1][j] = min(dis[1][j - 1], dis[0][j]) + seq[j];
			dis[1][n - 1] = min(dis[1][n - 1], dis[0][n - 1] + seq[n - 1]);
			for(int j = n - 2; j >= 0; --j)
				dis[1][j] = min(dis[1][j], dis[1][j + 1] + seq[j]);
			int clow = dis[1][0], cmsk = 0;
			for(int j = n - 1; j > 0; --j)
				cmsk = cmsk * 3 + (dis[1][j] - dis[1][j - 1] + 1);
			tr[pmsk][clow + n - 1].push_back(cmsk);
		}
	}
	for(int o = 2; o <= m; ++o)
	{
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0, sizeof f[0]);
		for(int plow = 0; plow < o; ++plow)
			for(int pmsk = 0; pmsk < maxs; ++pmsk)
			{
				if(!f[pre][plow][pmsk])
					continue;
				for(int dt = -min(plow, n - 1); dt <= 1; ++dt)
					for(auto &cmsk : tr[pmsk][dt + n - 1])
						mod_inc(f[cur][plow + dt][cmsk], f[pre][plow][pmsk]);
			}
	}
	// check mask
	for(int clow = 0; clow <= m; ++clow)
		for(int cmsk = 0; cmsk < maxs; ++cmsk)
		{
			if(!f[cur][clow][cmsk])
				continue;
			dis[0][0] = clow;
			for(int i = 1, tp = cmsk; i < n; ++i, tp /= 3)
				dis[0][i] = dis[0][i - 1] + (tp % 3 - 1);
			mod_inc(ans[dis[0][n - 1]], f[cur][clow][cmsk]);
		}
	for(int i = 0; i < n + m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
