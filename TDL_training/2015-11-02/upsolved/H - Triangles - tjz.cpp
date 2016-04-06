#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int maxn = 101;
int n[3], x0, y0, cnt[2][maxn][maxn], ans0, ans1;
struct Point
{
	int x, y;
	int det(const Point &t) const
	{
		return x * t.y - y * t.x;
	}
	bool operator < (const Point &t) const
	{
		return det(t) > 0;
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
} p[3][maxn];
int main()
{
	x0 = -10007;
	y0 = -10009;
	for(int Case = 1; scanf("%d%d%d", n + 0, n + 1, n + 2) == 3 && n[0] >= 0 && n[1] >= 0 && n[2] >= 0; ++Case)
	{
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < n[i]; ++j)
				scanf("%d%d", &p[i][j].x, &p[i][j].y);
		if(n[2] < 3)
		{
			printf("Case %d: 0 0\n", Case);
			continue;
		}
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < n[i]; ++j)
			{
				p[i][j].x -= x0;
				p[i][j].y -= y0;
			}
		sort(p[2], p[2] + n[2]);
		for(int t = 0; t < 2; ++t)
			for(int i = 0; i < n[2]; ++i)
				for(int j = i + 1; j < n[2]; ++j)
				{
					cnt[t][i][j] = 0;
					for(int k = 0; k < n[t]; ++k)
						if(p[2][i].det(p[t][k]) >= 0 && p[2][j].det(p[t][k]) <= 0
						&& (p[2][j] - p[2][i]).det(p[t][k] - p[2][i]) <= 0)
							++cnt[t][i][j];
				}
		ans0 = ans1 = 0;
		for(int i = 0; i < n[2]; ++i)
			for(int j = i + 1; j < n[2]; ++j)
				for(int k = j + 1; k < n[2]; ++k)
				{
					int sum0 = abs(cnt[0][i][j] + cnt[0][j][k] - cnt[0][i][k]);
					int sum1 = abs(cnt[1][i][j] + cnt[1][j][k] - cnt[1][i][k]);
					if(sum0 < sum1)
						++ans1;
					else if(sum0 > sum1)
						++ans0;
				}
		printf("Case %d: %d %d\n", Case, ans0, ans1);
	}
	return 0;
}
