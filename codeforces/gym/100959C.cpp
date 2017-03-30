#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 201, BASE = 10000, maxm = BASE * 6 + 1, INF = 0x3f3f3f3f; // [-BASE, 2BASE]
int n, m, a[maxn], dis[maxm], que[maxm], L, R;
inline bool valid(int x)
{
	return -BASE <= x && x <= BASE << 1;
}
inline int idx(int x, int o)
{
	return (x + BASE) << 1 | o;
}
inline int rdx(int id, int &x, int &o)
{
	x = (id >> 1) - BASE;
	o = id & 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	memset(dis, 0x3f, sizeof dis);
	dis[idx(0, 0)] = 0;
	que[R++] = idx(0, 0);
	while(L < R)
	{
		int udx = que[L++], ux, uo;
		rdx(udx, ux, uo);
		for(int i = 0; i < n; ++i)
		{
			int vx = a[i] - ux;
			if(!valid(vx))
				continue;
			int vo = uo ^ 1, vdx = idx(vx, vo);
			if(dis[vdx] != INF)
				continue;
			dis[vdx] = dis[udx] + 1;
			que[R++] = vdx;
		}
	}
	scanf("%d", &m);
	while(m--)
	{
		scanf("%d%d", &L, &R);
		if((L & 1) != (R & 1))
		{
			puts("-1");
			continue;
		}
		int res = std::min(dis[idx((L + R) >> 1, 1)], dis[idx((R - L) >> 1, 0)]);
		printf("%d\n", res != INF ? res : -1);
	}
	return 0;
}
