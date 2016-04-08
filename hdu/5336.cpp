#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10000, d[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
map<pair<int, int>, int> Hash;
int r, c, n, t, val[maxn], L, R, ans[maxn];
struct Point
{
	int o, x, y;
} a[maxn], que[maxn];
bool valid(int x, int y)
{
	return x >= 1 && x <= r && y >= 1 && y <= c;
}
int main()
{
	while(scanf("%d%d%d%d", &r, &c, &n, &t) == 4)
	{
		L = R = 0;
		Hash.clear();
		memset(ans, 0, sizeof ans);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d%d", &a[i].x, &a[i].y, &val[i]);
			Hash[make_pair(a[i].x, a[i].y)] = i;
		}
		int xx, yy;
		scanf("%d%d", &xx, &yy);
		for(int o = 0; o < 4; ++o)
		{
			int nx = xx + d[o][0], ny = yy + d[o][1];
			if(valid(nx, ny))
				que[R++] = (Point){o, nx, ny};
		}
		for(int i = 1; i <= t; ++i)
		{
			int RR = R;
			while(L != R)
			{
				Point now = que[L++];
				if(L >= maxn)
					L = 0;
				if(Hash.count(make_pair(now.x, now.y)))
				{
					int id = Hash[make_pair(now.x, now.y)];
					++val[id];
				}
				else
				{
					now.x += d[now.o][0];
					now.y += d[now.o][1];
					if(valid(now.x, now.y))
					{
						que[RR++] = now;
						if(RR >= maxn)
							RR = 0;
					}
				}
			}
			R = RR;
			for(int j = 1; j <= n; ++j)
				if(!ans[j] && val[j] > 4)
				{
					Hash.erase(make_pair(a[j].x, a[j].y));
					ans[j] = i;
					for(int o = 0; o < 4; ++o)
					{
						Point now = a[j];
						now.o = o;
						now.x += d[o][0];
						now.y += d[o][1];
						if(valid(now.x, now.y))
						{
							que[R++] = now;
							if(R >= maxn)
								R = 0;
						}
					}
				}
		}
		for(int i = 1; i <= n; ++i)
			if(!ans[i])
				printf("1 %d\n", val[i]);
			else
				printf("0 %d\n", ans[i]);
	}
	return 0;
}
