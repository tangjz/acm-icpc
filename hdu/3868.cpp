#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 20001;
const double eps = 1e-8;
int t, n;
double ans;
int dcmp(double x)
{
	return (x > eps) - (x < -eps);
}
double sqr(double x)
{
	return x * x;
}
struct Point
{
	int x, y;
	bool operator < (const Point &t) const
	{
		return x < t.x;
	}
} p[maxn], pp[maxn];
double dis(const Point &a, const Point &b)
{
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
double dis(const Point &a, const Point &b, const Point &c)
{
	return dis(a, b) + dis(b, c) + dis(a, c);
}
void upd(double &x, double y)
{
	if(x > y)
		x = y;
}
void solve(int L, int R)
{
	if(L + 2 >= R)
	{
		for(int i = L; i <= R; ++i)
		{
			int k = i;
			for(int j = i + 1; j <= R; ++j)
				if(p[j].y < p[k].y)
					k = j;
			if(k != i)
				swap(p[i], p[k]);
		}
		if(L + 2 == R)
			upd(ans, dis(p[L], p[L + 1], p[L + 2]));
		return;
	}
	int M = L + R >> 1, Mx = p[M].x, cnt = 0;
	solve(L, M);
	solve(M + 1, R);
	for(int i = L, j = M + 1; i <= M || j <= R; )
		if(i > M)
			pp[cnt++] = p[j++];
		else if(j > R)
			pp[cnt++] = p[i++];
		else if(p[i].y < p[j].y)
			pp[cnt++] = p[i++];
		else
			pp[cnt++] = p[j++];
	for(int i = 0; i < cnt; ++i)
		p[L + i] = pp[i];
	cnt = 0;
	for(int i = L; i <= R; ++i)
		if(2 * abs(p[i].x - Mx) <= ans)
			pp[cnt++] = p[i];
	for(int i = 0; i < cnt; ++i)
		for(int j = i + 1; j < cnt; ++j)
		{
			if(2 * (pp[j].y - pp[i].y) > ans)
				break;
			for(int k = j + 1; k < cnt; ++k)
				if(2 * (pp[k].y - pp[i].y) > ans)
					break;
				else
					upd(ans, dis(pp[i], pp[j], pp[k]));
		}
}
template<class T> void scan(T& x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	scan(t);
	while(t--)
	{
		ans = 1e10;
		scan(n);
		for(int i = 0; i < n; ++i)
			scan(p[i].x), scan(p[i].y);
		sort(p, p + n);
		solve(0, n - 1);
		printf("%.3f\n", ans);
	}
	return 0;
}
