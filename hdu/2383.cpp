#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
typedef pair<double, int> edge;
const int maxn = 101;
const double eps = 1e-10, INF = 1e10;
int dcmp(double x)
{
	if(fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1;
}
struct Point
{
	double x, y;
	bool operator < (const Point &t) const
	{
		return dcmp(x - t.x) < 0 || !dcmp(x - t.x) && dcmp(y - t.y) < 0;
	}
	Point operator + (const Point &t) const
	{
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
	Point operator * (const double &t) const
	{
		return (Point){x * t, y * t};
	}
	double det(const Point &t) const
	{
		return x * t.y - t.x * y;
	}
	double dot(const Point &t) const
	{
		return x * t.x + y * t.y;
	}
	double mode() const
	{
		return sqrt(x * x + y * y);
	}
} p[maxn], pp[maxn * 2];
int t, n, tot, cnt;
double r, dist[maxn * 2];
pair<Point, Point> seg[maxn];
vector<edge> e[maxn * 2];
priority_queue<edge, vector<edge>, greater<edge> > Q;
bool vis[maxn * 2];
bool valid(Point x)
{
	for(int i = 0; i < n; ++i)
		if(dcmp((x - p[i]).mode() - r) < 0)
			return 0;
	return 1;
}
bool cover(Point s, Point t)
{
	if(!dcmp((s - t).mode()))
		return 1;
	s = s + (t - s) * 0.001;//不明觉厉为啥不加会WA
	if(t < s)
		swap(s, t);
	cnt = 0;
	for(int i = 0; i < n; ++i)
	{
		Point t1 = t - s, t2 = p[i] - s;
		double dis = fabs(t1.det(t2)) / t1.mode();
		if(dcmp(dis - r) > 0)
			continue;
		Point oo = s + t1 * (t1.dot(t2) / t1.dot(t1));
		double ddd = sqrt(r * r - dis * dis);
		Point p1 = oo - t1 * (ddd / t1.mode()), p2 = oo + t1 * (ddd / t1.mode());
		if(p1 < s)
			p1 = s;
		if(t < p2)
			p2 = t;
		if(p1 < p2)
			seg[cnt++] = make_pair(p1, p2);
	}
	sort(seg, seg + cnt, less<pair<Point, Point> >());
	if(s < seg[0].first)
		return 0;
	Point last = seg[0].second;
	for(int i = 1; i < cnt; ++i)
	{
		if(last < seg[i].first)
			return 0;
		if(last < seg[i].second)
			last = seg[i].second;
	}
	if(last < t)
		return 0;
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 2;
		scanf("%lf%d%lf%lf%lf%lf", &r, &n, &pp[0].x, &pp[0].y, &pp[1].x, &pp[1].y);
		for(int i = 0; i < n; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
			{
				Point tmp = p[i] - p[j];
				if(dcmp(tmp.mode() - 2 * r) > 0 || !dcmp(tmp.mode()))
					continue;
				Point rev = (Point){tmp.y, -tmp.x}, oo = (p[i] + p[j]) * 0.5;
				double dis = sqrt(r * r - (tmp.x * tmp.x + tmp.y * tmp.y) / 4);
				rev = rev * (dis / rev.mode());
				Point t1 = oo + rev, t2 = oo - rev;
				if(valid(t1))
					pp[tot++] = t1;
				if(dcmp(rev.mode()) && valid(t2))
					pp[tot++] = t2;
			}
		for(int i = 0; i < tot; ++i)
			e[i].clear();
		for(int i = 0; i < tot; ++i)
			for(int j = i + 1; j < tot; ++j)
				if(cover(pp[i], pp[j]))
				{
					e[i].push_back(make_pair((pp[i] - pp[j]).mode(), j));
					e[j].push_back(make_pair((pp[i] - pp[j]).mode(), i));
				}
		memset(vis, 0, sizeof vis);
		for(int i = 0; i < tot; ++i)
			dist[i] = INF;
		while(!Q.empty())
			Q.pop();
		dist[0] = 0;
		Q.push(make_pair(dist[0], 0));
		while(!Q.empty())
		{
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			for(vector<edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int &v = it -> second;
				double &w = it -> first;
				if(dcmp(dist[v] - dist[u] - w) > 0)
				{
					dist[v] = dist[u] + w;
					Q.push(make_pair(dist[v], v));
				}
			}
		}
		if(!dcmp(dist[1] - INF))
			puts("-1");
		else
			printf("%.8f\n", dist[1]);
	}
	return 0;
}
