#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 25;
int t, n, nv, nh, v[maxn][3], h[maxn][3], ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		nv = nh = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			int x1, x2, y1, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if(x1 > x2)
				swap(x1, x2);
			if(y1 > y2)
				swap(y1, y2);
			if(x1 == x2)
			{
				v[nv][0] = x1;
				v[nv][1] = y1;
				v[nv++][2] = y2;
			}
			else
			{
				h[nh][0] = y1;
				h[nh][1] = x1;
				h[nh++][2] = x2;
			}
		}
		ans = 0;
		for(int i = 0; i < nh; ++i)
			for(int j = i + 1; j < nh; ++j)
				for(int p = 0; p < nv; ++p)
					for(int q = p + 1; q < nv; ++q)
					{
						int ey1 = max(v[p][1], v[q][1]), ey2 = min(v[p][2], v[q][2]);
						if(h[i][0] < ey1 || h[i][0] > ey2 || h[j][0] < ey1 || h[j][0] > ey2)
							continue;
						int ex1 = max(h[i][1], h[j][1]), ex2 = min(h[i][2], h[j][2]);
						if(v[p][0] < ex1 || v[p][0] > ex2 || v[q][0] < ex1 || v[q][0] > ex2)
							continue;
						++ans;
					}
		printf("%d\n", ans);
	}
	return 0;
}
