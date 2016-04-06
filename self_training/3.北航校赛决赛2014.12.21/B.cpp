#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxm = 1010;
int n;
long long m, x[maxm], l[maxm], h[maxm];
double f[maxm][3];
inline long long det(long long x1, long long y1, long long x2, long long y2)
{
	return x1 * y2 - x2 * y1;
}
inline double dis(long long x, long long y)
{
	return sqrt(x * x + y * y);
}
int main()
{
	while(scanf("%lld%d", &m, &n) == 2)
	{
		x[0] = l[0] = h[0] = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%lld%lld%lld", x + i, l + i, h + i);
			f[i][0] = f[i][1] = f[i][2] = 2e9;
		}
		f[0][0] = f[0][1] = f[0][2] = 0;
		for(int i = 0, lpos, hpos; i < n; ++i)
		{
			lpos = i + 1, hpos = i + 1;
			for(int j = i + 1; j <= n; ++j)
			{
				if(det(x[j] - x[i], l[j] - l[i], x[lpos] - x[i], l[lpos] - l[i]) <= 0)
				{
					if(det(x[j] - x[i], l[j] - l[i], x[hpos] - x[i], h[hpos] - l[i]) >= 0)
						f[j][0] = min(f[j][0], f[i][0] + dis(x[j] - x[i], l[j] - l[i]));
					lpos = j;
				}
				if(det(x[j] - x[i], h[j] - l[i], x[hpos] - x[i], h[hpos] - l[i]) >= 0)
				{
					if(det(x[j] - x[i], h[j] - l[i], x[lpos] - x[i], l[lpos] - l[i]) <= 0)
						f[j][1] = min(f[j][1], f[i][0] + dis(x[j] - x[i], h[j] - l[i]));
					hpos = j;
				}
				if(det(x[lpos] - x[i], l[lpos] - l[i], x[hpos] - x[i], h[hpos] - l[i]) < 0)
					break;
				if(l[lpos] <= l[i] && l[i] <= h[hpos])
					f[j][2] = min(f[j][2], f[i][0] + x[j] - x[i]);
			}
			lpos = i + 1, hpos = i + 1;
			for(int j = i + 1; j <= n; ++j)
			{
				if(det(x[j] - x[i], l[j] - h[i], x[lpos] - x[i], l[lpos] - h[i]) <= 0)
				{
					if(det(x[j] - x[i], l[j] - h[i], x[hpos] - x[i], h[hpos] - h[i]) >= 0)
						f[j][0] = min(f[j][0], f[i][1] + dis(x[j] - x[i], l[j] - h[i]));
					lpos = j;
				}
				if(det(x[j] - x[i], h[j] - h[i], x[hpos] - x[i], h[hpos] - h[i]) >= 0)
				{
					if(det(x[j] - x[i], h[j] - h[i], x[lpos] - x[i], l[lpos] - h[i]) <= 0)
						f[j][1] = min(f[j][1], f[i][1] + dis(x[j] - x[i], h[j] - h[i]));
					hpos = j;
				}
				if(det(x[lpos] - x[i], l[lpos] - h[i], x[hpos] - x[i], h[hpos] - h[i]) < 0)
					break;
				if(l[lpos] <= h[i] && h[i] <= h[hpos])
					f[j][2] = min(f[j][2], f[i][1] + x[j] - x[i]);
			}
		}
		int ans = 0;
		for(int i = 0; i <= n; ++i)
			if(m >= min(f[i][2], min(f[i][0], f[i][1])))
				ans = i;
		printf("%d\n", ans);
	}
	return 0;
}
