/*
 * 由于a,b,c相加得1 可以去掉一维 抽象成平面上的点 
 * 某两种材料可以和成两点间的所有材料 以此类推 
 * 即求最少种材料组成的凸包 包含所有所需材料 
 * 找出在所有点同侧的线段 求有向图最小环 
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-10;
const int INF = 0x1f1f1f1f;
struct Point
{
	double x, y;
	bool operator != (const Point &a) const { return x != a.x || y != a.y; }
	void init() { scanf("%lf%lf%lf", &x, &x, &y); }
} data[501], user[501];
int n, m, d[501][501], g[501][501], ans = INF;
bool vis[501];
inline double Area(Point a, Point b, Point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
int main()
{
	int i, j, k, tot = 0;
	scanf("%d%d", &n, &m);
	for(i = 0; i < n; ++i) data[i].init();
	for(i = 0; i < m; ++i) user[i].init();
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < m; ++j) if(data[i] != user[j]) break;
		if(j >= m) { printf("1\n"); return 0; }
	}
	memset(d, 0x1f, sizeof(d));
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) if(i != j)
		{
			for(k = 0; k < m; ++k) if(Area(data[i], data[j], user[k]) < -eps) break;
			if(k >= m) vis[i] = vis[j] = 1;
		}
	for(i = 0; i < n; ++i) if(vis[i]) data[tot++] = data[i];
	n = tot;
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) if(i != j)
		{
			for(k = 0; k < m; ++k) if(Area(data[i], data[j], user[k]) < -eps) break;
			if(k >= m) d[i][j] = 1;
		}
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) if(d[i][j] == 1 && d[j][i] == 1)
		{
			double maxx = max(data[i].x, data[j].x), minx = min(data[i].x, data[j].x), maxy = max(data[i].y, data[j].y), miny = min(data[i].y, data[j].y);
			for(k = 0; k < m; ++k) if(user[k].x < minx || user[k].x > maxx || user[k].y < miny || user[k].y > maxy) break;
			if(k >= m) { printf("2\n"); return 0; }
		}
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j) g[i][j] = d[i][j];
	for(k = 0; k < n; ++k)
	{
		for(i = 0; i < n; ++i) if(i != k)
			for(j = 0; j < n; ++j) if(j != i && j != k)
				ans = min(ans, d[i][j] + g[j][k] + g[k][i]);
		for(i = 0; i < n; ++i)
			for(j = 0; j < n; ++j) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	}
	if(ans < INF) printf("%d\n", ans);
	else printf("-1\n");
	return 0;
}
