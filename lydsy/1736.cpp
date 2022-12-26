#include <queue>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 301, maxs = 90001, maxd = 4, dx[maxd] = {1, 0, -1, 0}, dy[maxd] = {0, 1, 0, -1};
int n, m, a[maxs], ans;
priority_queue<pair<int, int> > Q;
bool vis[maxs];
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx)
		{
			scanf("%d", a + idx);
			if(i == 0 || i == n - 1 || j == 0 || j == m - 1)
			{
				Q.push(make_pair(-a[idx], idx));
				vis[idx] = 1;
			}
		}
	while(!Q.empty())
	{
		pair<int, int> u = Q.top();
		Q.pop();
		ans += -u.first - a[u.second];
		int ux = u.second / m, uy = u.second % m;
		for(int i = 0; i < maxd; ++i)
		{
			int vx = ux + dx[i], vy = uy + dy[i], vdx;
			if(vx >= 0 && vx < n && vy >= 0 && vy < m && !vis[vdx = vx * m + vy])
			{
				Q.push(make_pair(-max(-u.first, a[vdx]), vdx));
				vis[vdx] = 1;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
