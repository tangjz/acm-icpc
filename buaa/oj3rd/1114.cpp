#include <cmath>
#include <cstdio>
#include <cstring>
const int maxn = 101;
const double eps = 1e-12;
int n, l, r, a[maxn], b[maxn], c[maxn], s[maxn];
inline int dcmp(double x)
{
	if(fabs(x) < eps)
		return 0;
	return 0 < x ? 1 : -1;
}
inline double area(int id, double L, double R)
{
	return ((1.0 / 3 * a[id] * R + 1.0 / 2 * b[id]) * R + c[id]) * R - ((1.0 / 3 * a[id] * L + 1.0 / 2 * b[id]) * L + c[id]) * L;
}
inline double f(int id, double x)
{
	return (a[id] * x + b[id]) * x + c[id];
}
double lastx, lasty, ans;
bool Area(int id, double L, double R)
{
	if(!dcmp(lastx - L) && dcmp(lasty - f(id, L)))
		return 0;
	ans += area(id, L, R);
	lastx = R;
	lasty = f(id, lastx);
	return 1;
}
int main()
{
	while(scanf("%d%d%d", &n, &l, &r) == 3)
	{
		bool flag = 1;
		for(int i = 0; i < n; ++i)
			scanf("%d%d%d%d", a + i, b + i, c + i, s + i);
		ans = 0.0;
		lastx = l - 1;
		for(int i = 0; i < n; ++i)
		{
			int L = s[i], R = i == n - 1 ? r : s[i + 1];
			if(!a[i])
			{
				if(!b[i])
				{
					if(c[i] > 0)
						flag &= Area(i, L, R);
				}
				else
				{
					double x = -(double)c[i] / b[i];
					if(dcmp(f(i, L)) >= 0 && dcmp(f(i, R)) >= 0)
						flag &= Area(i, L, R);
					else if(dcmp(f(i, L)) > 0)
						flag &= Area(i, L, x);
					else if(dcmp(f(i, R)) > 0)
						flag &= Area(i, x, R);
				}
			}
			else
			{
				if(b[i] * b[i] - 4 * a[i] * c[i] <= 0)
				{
					if(a[i] > 0)
						flag &= Area(i, L, R);
				}
				else
				{
					double x1 = (-b[i] - sqrt(b[i] * b[i] - 4 * a[i] * c[i])) / (2 * a[i]), x2 = (-b[i] + sqrt(b[i] * b[i] - 4 * a[i] * c[i])) / (2 * a[i]);
					double RR = x1 < R ? x1 : R, LL = L < x2 ? x2 : L;
					if(a[i] > 0)//x1 < x2
					{
						if(dcmp(L - RR) < 0)
							flag &= Area(i, L, RR);
						if(dcmp(LL - R) < 0)
							flag &= Area(i, LL, R);
					}
					else//x1 > x2
					{
						if(dcmp(LL - RR) < 0)
							flag &= Area(i, LL, RR);
					}
				}
			}
			if(i)
			{
				double f1 = f(i - 1, s[i]), f2 = f(i, s[i]);
				if(dcmp(f1) >= 0 && dcmp(f2) >= 0 && dcmp(f1 - f2) || dcmp(f1) * dcmp(f2) < 0)
					flag = 0;
			}
			if(!flag)
				break;
		}
		if(!flag)
			puts("0.000");
		else
			printf("%.3f\n", ans);
	}
	return 0;
}
