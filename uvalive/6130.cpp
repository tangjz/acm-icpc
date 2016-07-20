#include <cmath>
#include <cstdio>
#include <algorithm>
const int maxt = 1000;
const double pi = acos(-1.0), eps = 1e-4, r = 5.0, INF = 1e3;
inline int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
inline int dcmp(double x, double y)
{
	return sgn(x - y);
}
int t;
double pos[4], ans;
struct Point
{
	double x, y;
	double dot(const Point &t) const
	{
		return x * t.x + y * t.y;
	}
	double det(const Point &t) const
	{
		return x * t.y - y * t.x;
	}
} p[4], tr, pp[4];
int check(double theta)
{
	tr = (Point){cos(theta), sin(theta)};
	pos[0] = pos[1] = INF;
	pos[2] = pos[3] = -INF;
	for(int i = 0; i < 4; ++i)
	{
		pp[i] = (Point){p[i].dot(tr), -p[i].det(tr)};
		pos[0] = std::min(pos[0], pp[i].x);
		pos[1] = std::min(pos[1], pp[i].y);
		pos[2] = std::max(pos[2], pp[i].x);
		pos[3] = std::max(pos[3], pp[i].y);
	}
	return pos[2] - pos[0] < pos[3] - pos[1];
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		for(int i = 0; i < 4; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		ans = -INF;
		for(int i = 0; i < maxt; ++i)
		{
			double L = (double)i / maxt * pi, R = (i + 1.0) / maxt * pi;
			int qL = check(L), qR = check(R);
			if(qL * qR > 0)
				continue;
			while(R - L >= 1e-8)
			{
				double M = (L + R) * 0.5;
				qR = check(M);
				if(qL * qR > 0)
				{
					L = M;
					qL = qR;
				}
				else
					R = M;
			}
			check(L);
			if(dcmp(pos[2] - pos[0], pos[3] - pos[1]) != 0)
				continue;
			int cr[4] = {}, cl[4] = {};
			for(int j = 0; j < 4; ++j)
			{
				if(dcmp(pp[j].x, pos[0]) == 0)
					++cr[j], ++cl[0];
				if(dcmp(pp[j].y, pos[1]) == 0)
					++cr[j], ++cl[1];
				if(dcmp(pp[j].x, pos[2]) == 0)
					++cr[j], ++cl[2];
				if(dcmp(pp[j].y, pos[3]) == 0)
					++cr[j], ++cl[3];
			}
			bool flag = 1;
			for(int j = 0; j < 4 && flag; ++j)
				flag &= cr[j] == 1 && cl[j] == 1;
			if(flag)
				ans = std::max(ans, 0.5 * ((pos[2] - pos[0]) + (pos[3] - pos[1])) + 2 * r);
		}
		if(sgn(ans) <= 0)
			printf("Case %d: no solution\n", Case);
		else
			printf("Case %d: %.2f\n", Case, ans);
	}
	return 0;
}
