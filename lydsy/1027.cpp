#include <cstdio>
#include <cstring>
const int maxn = 510, maxm = 510, INF = 0x3f3f3f3f;
const double eps = 1e-10;
int t, n, m, g[maxm][maxm], ans;
int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
struct Point
{
	double x, y;
	bool operator == (const Point &t) const
	{
		return !sgn(x - t.x) && !sgn(y - t.y);
	}
	double dot(const Point &t) const
	{
		return x * t.x + y * t.y;
	}
	double det(const Point &t) const
	{
		return x * t.y - y * t.x;
	}
	double mode2() const
	{
		return dot(*this);
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
} p[maxn], pp[maxm];
int main()
{
	int tmp;
	scanf("%d%d", &m, &n);
	for(int i = 0; i < m; ++i)
		scanf("%lf%lf%*lf", &pp[i].x, &pp[i].y);
	for(int i = 0; i < n; ++i)
		scanf("%lf%lf%*lf", &p[i].x, &p[i].y);
	if(m == 1)
	{
		bool flag = 0;
		for(int i = 0; i < n; ++i)
			if(!(p[i] == pp[0]))
			{
				flag = 1;
				break;
			}
		printf("%d\n", !flag ? 1 : -1);
		return 0;
	}
	memset(g, 0x3f, sizeof g);
	for(int i = 0; i < m; ++i)
	{
		int top = -1, dep = -1;
		bool flag = 0;
		for(int j = 0; j < n; ++j)
		{
			if(p[j] == pp[i])
				continue;
			if(top != -1 && top == dep && !sgn((p[top] - pp[i]).det(p[j] - pp[i])) && sgn((p[top] - pp[i]).dot(p[j] - pp[i])))
			{
				top = j;
				flag = 1;
				continue;
			}
			if(flag && sgn((p[top] - pp[i]).det(p[j] - pp[i])) > 0 && sgn((p[dep] - pp[i]).det(p[j] - pp[i])) < 0)
			{
				top = top + dep;
				dep = top - dep;
				top = top - dep;
				flag = 0;
				continue;
			}
			if(top == -1 || sgn((p[top] - pp[i]).det(p[j] - pp[i])) > 0)
			{
				top = j;
				if(dep != -1 && sgn((p[dep] - pp[i]).det(p[top] - pp[i])) < 0)
					break;
			}
			if(dep == -1 || sgn((p[dep] - pp[i]).det(p[j] - pp[i])) < 0)
			{
				dep = j;
				if(sgn((p[dep] - pp[i]).det(p[top] - pp[i])) < 0)
					break;
			}
		}
		if(top != -1 && sgn((p[dep] - pp[i]).det(p[top] - pp[i])) < 0)
			continue;
		Point L = (p[top] - pp[i]) * -1.0, R = p[dep] - pp[i];
		for(int j = 0; j < m; ++j)
			if(i != j)
			{
				int sg1 = sgn(L.det(pp[j] - pp[i])), sg2 = sgn(R.det(pp[j] - pp[i]));
				if(sg1 > 0 && sg2 <= 0 || sg1 >= 0 && sg2 < 0 || !sg1 && !sg2 && sgn(R.dot(pp[j] - pp[i])) >= 0)
	 				g[i][j] = 1;// printf("edge %d to %d\n", i, j);
			}
	}
	for(int k = 0; k < m; ++k)
		for(int i = 0; i < m; ++i) if(g[i][k] != INF)
			for(int j = 0; j < m; ++j) if(g[k][j] != INF)
				if(g[i][j] > g[i][k] + g[k][j])
					g[i][j] = g[i][k] + g[k][j];
	ans = INF;
	for(int i = 0; i < m; ++i)
		if(ans > g[i][i])
			ans = g[i][i];
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}
